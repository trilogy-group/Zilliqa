# Zilliqa Development with DF Devspaces

## Install DF Devspaces

1. Create and install devspaces client as it is written in help guide https://support.devspaces.io/article/22-devspaces-client-installation.

2. Here is some details about DF Devspaces https://devspaces.io/devspaces/help

Here follows the main commands used in Devspaces cli. 

|action   |Description                                                                                   |
|---------|----------------------------------------------------------------------------------------------|
|`devspaces --help`                    |Check the available command names.                               |
|`devspaces create [options]`          |Creates a DevSpace using your local DevSpaces configuration file |
|`devspaces start <devSpace>`          |Starts the DevSpace named \[devSpace\]                           |
|`devspaces bind <devSpace>`           |Syncs the DevSpace with the current directory                    |
|`devspaces info <devSpace> [options]` |Displays configuration info about the DevSpace.                  |

Use `devspaces --help` to know about updated commands.


### Start Devspaces

It is assumed that you opened a terminal in `devspaces` folder of the repository.

1.  Create DevSpaces.

```bash
devspaces create
```

2. Start your devspaces.
```bash
devspaces start zilliqa
```

3. Start containers synchronization
Open terminal on folder you want to sync with devspaces and run:

```bash
cd ..
devspaces bind zilliqa
```
4. Grab some container info

```bash
devspaces info zilliqa
```

Retrieve published DNS, endpoints using this command and 

5. Connect to development container

```bash
devspaces exec zilliqa
```

6. Build the application
```bash
./build.sh
```

7. Run the local testnet script in build directory
```bash
cd build && ./tests/Node/test_node_simple.sh
```

8. If you would like to terminate Zilliqa, run:
```bash
pkill zilliqa
```

## Running Zilliqa via Docker-Compose file

Currently, we have these command available to work using local docker compose.

```bash
devspaces/docker-cli.sh <command>
```

|action    |Description                                                               |
|----------|--------------------------------------------------------------------------|
|`build`   |Builds images                                                             |                                      
|`deploy`  |Deploy Docker compose containers                                          |
|`undeploy`|Undeploy Docker compose containers                                        |
|`start`   |Starts Docker compose containers                                          |
|`stop`    |Stops Docker compose containers                                           |
|`exec`    |Get into the container                                                    |


### Dockerfile
 Dockefile is created on top of `ubuntu:18.04` image.

### Requirements
 - The project should be cloned from https://github.com/trilogy-group/Zilliqa.git
 - Docker version 18.09.0-ce
 - Docker compose version 1.23.1 

### Quick Start
- Clone the repository
- Open a terminal session to that folder
- Run `./docker-cli.sh deploy`
- Run `./docker-cli.sh exec`

- At this point you must be inside the docker container.
- When you finish working with the container, type `exit`
- Run `./docker-cli.sh stop` to stop running service.
- Run `./docker-cli.sh start` to start stopped container (should be used only after `stop` command).
- Run `./docker-cli.sh undeploy` to stop and remove running service







