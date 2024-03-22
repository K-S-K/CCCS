# CCSS - Cross Container Client-Server Example
The purpose of this project is to adjust the approach of creating several projects in **different docker containers** and let them **communicate with each other** via sockets. The project can be used as a template for creating more complex projects.

## The concepts implemented in the job are:
- There are two separate processes: the Emitter and the Collector.
- The Collector listens to the input from the Emitter and answers in the same socket.
- The applications are the simplest programs in C / C++.
- The build process is performed in the Docker containers.
- The executables are copied to the new clean containers after the build, so the source code doesn't go to production.
- The Docker-compose script creates the dockers.
- The executables are stored in the /app directory of each container.


## To start the Emitter and the Collector
- Go to the Src directory
- Type the command:
```
docker-compose up --build
```
- Or this command:
```
docker-compose up --force-recreate
```
![How deit looks now](Doc/Fig.01-Debug-complete.png)

## History (just milestone steps)
- [2024.03.21 - Make Makefiles more readable](https://github.com/K-S-K/CCCS/pull/10/files)
- [2024.03.21 - Add an Event Subscription](https://github.com/K-S-K/CCCS/pull/8/files)

## Other notes
- Developed with Visual Studio Code under Ubuntu.
