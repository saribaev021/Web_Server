#ifndef WEB_SERVER_EXECUTOR_HPP
#define WEB_SERVER_EXECUTOR_HPP

#include <list>
#include <iostream>
#include <unistd.h>
#include <vector>

class Executor {
private:
    char **arrayEnv;
    char **launch;
    int fdIn[2];
    int fdOut[2];
    std::string body;
    Client _client;
public:
    Executor(char **arrayEnv, const std::string &launcher, const std::string &scrypt, const std::string &body, const Client &client) :
            arrayEnv(arrayEnv), body(body), _client(client){
        launch = (char **) malloc(sizeof(char *) * 3);
        launch[0] = strdup(launcher.c_str());
        launch[1] = strdup(("./" + scrypt).c_str());
        launch[2] = NULL;
    }

    char **getArrayEnv() const {
        return arrayEnv;
    }

    Executor &launcher();

    Executor &putBody();

    Executor &inputBody();

    void pipeFd();

    const std::string &getBody() const;

    char **getLaunch() const;
};

Executor &Executor::launcher() {
    int status = 0;

    pid_t pid = fork();
    write(fdIn[1], "\n", 1);
    close(fdIn[1]);
    if (pid == 0) {
        dup2(fdIn[0], 0);
        dup2(fdOut[1], 1);
//        for(int i = 0; getArrayEnv()[i] != NULL; i++)
//            std::cerr<<getArrayEnv()[i]<<std::endl;
        chdir(_client.getHttp().getStartLine().find("change_location")->second.c_str());
        status = execve(getLaunch()[0], getLaunch(), getArrayEnv());
        exit(status);
    } else if (pid < 0)
        write(2, "Error Fork", 10);
    pid = waitpid(pid, &status, WUNTRACED);
    close(fdIn[0]);
    close(fdOut[1]);
    return *this;
}

Executor &Executor::putBody() {
    if (!body.empty()) {
        write(fdIn[1], body.c_str(), body.length());
    }
    return *this;
}

Executor &Executor::inputBody() {
    char buf[5];
    bzero(buf, 5);
    int len = 0;
    while ((len = read(fdOut[0], buf, 4)) > 0) {
        buf[len] = '\0';
        body += buf;
    }
    return *this;
}

void Executor::pipeFd() {
    pipe(fdIn);
    pipe(fdOut);
}

const std::string &Executor::getBody() const {
    return body;
}

char **Executor::getLaunch() const {
    return launch;
}


#endif //WEB_SERVER_EXECUTOR_HPP
