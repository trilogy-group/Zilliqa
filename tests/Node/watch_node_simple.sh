#!/bin/bash
# Copyright (c) 2018 Zilliqa 
# This source code is being disclosed to you solely for the purpose of your participation in 
# testing Zilliqa. You may view, compile and run the code for that purpose and pursuant to 
# the protocols and algorithms that are programmed into, and intended by, the code. You may 
# not do anything else with the code without express permission from Zilliqa Research Pte. Ltd., 
# including modifying or publishing the code (or any part of it), and developing or forming 
# another public or private blockchain network. This source code is provided ‘as is’ and no 
# warranties are given as to title or non-infringement, merchantability or fitness for purpose 
# and, to the extent permitted by law, all liability for your use of the code is disclaimed. 
# Some programs in this code are governed by the GNU General Public License v3.0 (available at 
# https://www.gnu.org/licenses/gpl-3.0.en.html) (‘GPLv3’). The programs that are governed by 
# GPLv3.0 are those programs that are located in the folders src/depends and tests/depends 
# and which include a reference to GPLv3 in their program files.

# Usage:
# 
#   run this script with 'watch':
#       watch -n1 tests/Node/watch_node_simple.sh'

for id in {1..20}
do
    port=$((5000 + $id))
    [ $id -lt 10 ] && id=0$id
    node_cmd_info=$(pgrep -f "zilliqa.*127\.0\.0\.1 $port" -a | cut -f1,5,6 -d" ")  
    node_log=$(tail -n1 local_run/node_00$id/zilliqa-00001-log.txt)
    if [[ -z $node_cmd_info ]]
    then
        node_cmd_info="dead"
        node_log=$(tail -n1 local_run/node_00$id/error_log_zilliqa)
    fi
    echo node $id: $node_cmd_info $node_log
done
