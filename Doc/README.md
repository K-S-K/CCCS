# CCSS - Cross Container Client-Server Example

#### To start the Emitter and the Collector
- Go to the Src directory
- Type the command 
```
docker-compose up --build
```
- Or another command 
```
docker-compose up --force-recreate
```


#### Other Useful Docker Commands:
- ```cd Src``` - this is the directory from which all commands must be called.
- ```docker-compose up --build``` - Update and start all containers.
- ```docker ps -a``` - List all the containers.
- ```docker rm -v -f $(docker ps -qa)``` - Clean out all containers on my development machine
- ```docker rm 42928f35f2f1 eecbbec31cb4``` - Remove these two containers.
- ```docker images -a``` - List all images
- ```docker rmi ccss-emitter ccss-collector``` - Remove these two images.
- ```docker image prune -a --force --filter "until=24h"``` - Remove all old images.
- 
- ```docker exec -it [container-id] bash``` - Enter to the Docker Container session with command line


#### Further reads:
- [Develop on a remote Docker host](https://code.visualstudio.com/remote/advancedcontainers/develop-remote-host)
- []()
- [Deploying Docker Containers over SSH](https://brunoscheufler.com/blog/2022-06-05-deploying-docker-containers-over-ssh)
- [Running SSH Server in a Docker container](https://satvikakolisetty.medium.com/running-ssh-server-in-a-docker-container-55eb2a3add35)
- [Setting Up a Local Docker Registry](https://www.allisonthackston.com/articles/local-docker-registry.html)
- [Creating a local Docker registry](https://kubeops.net/blog/creating-a-local-docker-registry)
- [How to Use Your Own Registry](https://www.docker.com/blog/how-to-use-your-own-registry-2/)
- []()
- [C++ Development Tutorial 4: Static and Dynamic Libraries](https://domiyanyue.medium.com/c-development-tutorial-4-static-and-dynamic-libraries-7b537656163e)
- []()
- [Inter-process communication in Linux: Sockets and signals](https://opensource.com/article/19/4/interprocess-communication-linux-networking)
- [Code memory safety and efficiency by example](https://opensource.com/article/21/8/memory-programming-c)
- [A guide to understanding Linux software libraries in C](https://opensource.com/article/21/2/linux-software-libraries)
- [Inter-process communication in Linux: Using pipes and message queues](https://opensource.com/article/19/4/interprocess-communication-linux-channels)
- [Inter-process communication in Linux: Shared storage](https://opensource.com/article/19/4/interprocess-communication-linux-storage)
- []()
- [C++ 17 New Features and Trick](https://www.codeproject.com/Articles/5262072/Cplusplus-17-New-Features-and-Trick)
- []()
- [Sending a C++ Class Object over a socket?](https://ubuntuforums.org/showthread.php?t=687947)
- [De-/Serialization of structs representing TCP messages](https://codereview.stackexchange.com/questions/260597/de-serialization-of-structs-representing-tcp-messages)
- [serialize and deserialize structures in sockets](https://stackoverflow.com/questions/14392715/serialize-and-deserialize-structures-in-sockets)
- []()
- [protobuf on github.com](https://github.com/protocolbuffers/protobuf)
- [Protocol Buffers Documentation](https://protobuf.dev/)
- [Protocol Buffer Basics: C++](https://protobuf.dev/getting-started/cpptutorial/)
- []()
- []()
- []()
