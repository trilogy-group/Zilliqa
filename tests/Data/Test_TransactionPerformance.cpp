/**
* Copyright (c) 2018 Zilliqa
* This source code is being disclosed to you solely for the purpose of your participation in
* testing Zilliqa. You may view, compile and run the code for that purpose and pursuant to
* the protocols and algorithms that are programmed into, and intended by, the code. You may
* not do anything else with the code without express permission from Zilliqa Research Pte. Ltd.,
* including modifying or publishing the code (or any part of it), and developing or forming
* another public or private blockchain network. This source code is provided ‘as is’ and no
* warranties are given as to title or non-infringement, merchantability or fitness for purpose
* and, to the extent permitted by law, all liability for your use of the code is disclaimed.
* Some programs in this code are governed by the GNU General Public License v3.0 (available at
* https://www.gnu.org/licenses/gpl-3.0.en.html) (‘GPLv3’). The programs that are governed by
* GPLv3.0 are those programs that are located in the folders src/depends and tests/depends
* and which include a reference to GPLv3 in their program files.
**/

#include "libCrypto/Schnorr.h"
#include "libCrypto/Sha2.h"
#include "libData/AccountData/Account.h"
#include "libData/AccountData/Address.h"
#include "libData/AccountData/Transaction.h"
#include "libUtils/DataConversion.h"
#include "libUtils/Logger.h"
#include <array>
#include <string>
#include <vector>

#define BOOST_TEST_MODULE transactiontest
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace boost::multiprecision;
using namespace std;

using KeyPair = std::pair<PrivKey, PubKey>;

BOOST_AUTO_TEST_SUITE(TransactionPrefillPerformance)

// decltype(auto) GenWithSigning(const KeyPair& sender, const KeyPair& receiver,
//                               size_t n)
// {
//     LOG_MARKER();
//     unsigned int version = 0;
//     auto nonce = 0;

//     const auto& fromPrivKey = sender.first;
//     const auto& fromPubKey = sender.second;
//     auto toAddr = Account::GetAddressFromPublicKey(receiver.second);

//     std::vector<Transaction> txns;
//     txns.reserve(n);

//     for (auto i = 0u; i < n; i++)
//     {
//         auto amount = i;

//         Transaction txn{version,    nonce,  toAddr,
//                         fromPubKey, amount, {/* empty sig */}};

//         std::vector<unsigned char> buf;
//         txn.SerializeWithoutSignature(buf, 0);

//         Signature sig;
//         Schnorr::GetInstance().Sign(buf, fromPrivKey, fromPubKey, sig);

//         vector<unsigned char> sigBuf;
//         sig.Serialize(sigBuf, 0);
//         txn.SetSignature(sigBuf);

//         txns.emplace_back(move(txn));
//     }

//     return txns;
// }

// decltype(auto) GenWithoutSigning(const KeyPair& sender, const KeyPair& receiver,
//                                  size_t n)
// {
//     LOG_MARKER();
//     unsigned int version = 0;
//     auto nonce = 0;

//     // const auto &fromPrivKey = sender.first;
//     const auto& fromPubKey = sender.second;
//     auto toAddr = Account::GetAddressFromPublicKey(receiver.second);

//     std::vector<Transaction> txns;
//     txns.reserve(n);

//     for (auto i = 0u; i < n; i++)
//     {
//         auto amount = i;

//         Transaction txn{version,    nonce,  toAddr,
//                         fromPubKey, amount, {/* empty sig */}};

//         std::vector<unsigned char> buf;
//         txn.SerializeWithoutSignature(buf, 0);

//         // Signature sig;
//         // Schnorr::GetInstance().Sign(buf, fromPrivKey, fromPubKey, sig);

//         // vector<unsigned char> sigBuf;
//         // sig.Serialize(sigBuf, 0);
//         // txn.SetSignature(sigBuf);

//         txns.emplace_back(move(txn));
//     }

//     return txns;
// }

// decltype(auto) GenWithoutSigningAndSerializing(const KeyPair& sender,
//                                                const KeyPair& receiver,
//                                                size_t n)
// {
//     LOG_MARKER();
//     unsigned int version = 0;
//     auto nonce = 0;

//     // const auto &fromPrivKey = sender.first;
//     const auto& fromPubKey = sender.second;
//     auto toAddr = Account::GetAddressFromPublicKey(receiver.second);

//     std::vector<Transaction> txns;
//     txns.reserve(n);

//     for (auto i = 0u; i < n; i++)
//     {
//         auto amount = i;

//         Transaction txn{version,    nonce,  toAddr,
//                         fromPubKey, amount, {/* empty sig */}};

//         // std::vector<unsigned char> buf;
//         // txn.SerializeWithoutSignature(buf, 0);

//         // Signature sig;
//         // Schnorr::GetInstance().Sign(buf, fromPrivKey, fromPubKey, sig);

//         // vector<unsigned char> sigBuf;
//         // sig.Serialize(sigBuf, 0);
//         // txn.SetSignature(sigBuf);

//         txns.emplace_back(move(txn));
//     }

//     return txns;
// }

decltype(auto) GenWithDummyValue(const KeyPair& sender, const KeyPair& receiver,
                                 size_t n)
{
    LOG_MARKER();
    std::vector<Transaction> txns;

    // Generate to account
    uint256_t version = 1;
    uint256_t nonce = 0;
    Address toAddr = Account::GetAddressFromPublicKey(receiver.second);
    uint256_t amount = 123;
    uint256_t gasPrice = 456;
    uint256_t gasLimit = 789;

    for (unsigned i = 0; i < n; i++)
    {
        Transaction txn(version, nonce, toAddr, sender, amount, gasPrice,
                        gasLimit, {}, {});

        // LOG_MESSAGE2(to_string(m_mediator.m_currentEpochNum).c_str(),
        // "Created txns: " << txn.GetTranID())
        // LOG_MESSAGE(txn.GetSerializedSize());

        txns.emplace_back(txn);
        nonce++;
        amount++;
        gasPrice++;
        gasLimit++;
    }

    return txns;
}

BOOST_AUTO_TEST_CASE(GenTxn1000)
{
    INIT_STDOUT_LOGGER();
    auto n = 1000u;
    auto sender = Schnorr::GetInstance().GenKeyPair();
    auto receiver = Schnorr::GetInstance().GenKeyPair();

    //LOG_GENERAL(INFO, "Generating " << n << " txns with multiple methods");

    // auto t_start = std::chrono::high_resolution_clock::now();
    // auto txns1 = GenWithSigning(sender, receiver, n);
    // auto t_end = std::chrono::high_resolution_clock::now();

    // LOG_GENERAL(
    //     INFO,
    //     (std::chrono::duration<double, std::milli>(t_end - t_start).count())
    //         << " ms");

    // t_start = std::chrono::high_resolution_clock::now();
    // auto txns2 = GenWithoutSigning(sender, receiver, n);
    // t_end = std::chrono::high_resolution_clock::now();

    // LOG_GENERAL(
    //     INFO,
    //     (std::chrono::duration<double, std::milli>(t_end - t_start).count())
    //         << " ms");

    // t_start = std::chrono::high_resolution_clock::now();
    // auto txns3 = GenWithoutSigningAndSerializing(sender, receiver, n);
    // t_end = std::chrono::high_resolution_clock::now();

    // LOG_GENERAL(
    //     INFO,
    //     (std::chrono::duration<double, std::milli>(t_end - t_start).count())
    //         << " ms");

    LOG_GENERAL(INFO, "Generating " << n << " txns with dummy values");

    auto t_start = std::chrono::high_resolution_clock::now();
    auto txns4 = GenWithDummyValue(sender, receiver, n);
    auto t_end = std::chrono::high_resolution_clock::now();

    LOG_GENERAL(
        INFO,
        (std::chrono::duration<double, std::milli>(t_end - t_start).count())
            << " ms");
}

BOOST_AUTO_TEST_SUITE_END()
