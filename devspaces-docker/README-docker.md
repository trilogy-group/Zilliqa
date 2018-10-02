# Dockerfile

Dockefile is created on top of `ubuntu` image.

# Requirements

 - The project should be cloned from https://github.com/Zilliqa/Zilliqa
 - Docker version 18.06.1-ce
 - Docker compose version 1.22.0
  
# Quick Start

- Open a terminal session from the project root folder
- Run `devspaces-docker/docker build`
- Run `devspaces-docker/docker up`
- Run `devspaces-docker/docker exec builder bash`
- At this point you must be inside the docker container, in the root folder of the project. From there, you can run the commands as usual:
	- `./build.sh` to build the project.
	- `cd build && ./tests/Node/test_node_simple.sh` to run the local testnet script in build directory
	- `pkill zilliqa` to terminate zilliqa

NOTE: If on your local environment you are using a root user, you might need to run `sudo chown -R dev:dev /data` before starting to build.
	
- When you finish working with the container, type `exit`
- Run `devspaces-docker/docker down` to stop the service.

## Build the image

In `{project-root-folder}/` folder, run:

```bash
devspaces-docker/docker build
```

This instruction will create a DockerImage in your machine called `zilliqa_builder:latest`

## Run the container

In `{project-root-folder}/` folder, run:

```bash
devspaces-docker/docker up
```

This command will create a running container in detached mode called `builder`.
You can check the containers running with `docker ps`

## Get a container session

In `{project-root-folder}/` folder, run:

```bash
devspaces-docker/docker exec
```

## docker-compose.yml

The docker-compose.yml file contains a single service: `builder`.
We will use this service to build the Zilliqa sources from our local environment, so we mount root project dir `.` to the a `/data` folder:

```yaml
    volumes:
      - .:/data:Z
```

Please refer to [Contributing](CONTRIBUTING.md) doc for more details on the building and running the app.
