#ifndef WEB_SERVER_EXECUTOR_HPP
#define WEB_SERVER_EXECUTOR_HPP

#include <list>
#include <iostream>
#include <unistd.h>
#include <vector>

class Executor{
private:
	char **arrayEnv;
    char **launch;
	int fdIn[2];
	int fdOut[2];
	std::string body;
public:
	Executor(char **arrayEnv, const std::string &launcher, const std::string &scrypt, const std::string& body):
	arrayEnv(arrayEnv), body(body) {
        launch = (char**)malloc(sizeof(char*) * 3);
        launch[0] = strdup(launcher.c_str());
        launch[1] = strdup(scrypt.c_str());
        launch[2] = NULL;
        return array;
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
	close(fdIn[1]);
	if (pid == 0){
		dup2(fdIn[0], 0);
		dup2(fdOut[1], 1);
		status = execve(getLaunch()[0], getLaunch(), getArrayEnv());
		exit(status);
	}else if (pid < 0)
		write(2, "Error Fork", 10);
	pid = waitpid(pid, &status, WUNTRACED);
	write(2, "Check fork", 10);
	close(fdIn[0]);
	close(fdOut[1]);
	return *this;
}

Executor &Executor::putBody() {
	if (!body.empty()){
		write(fdIn[1], body.c_str(), body.length());
	} else
	    write(fdIn[1], "\n", 1);
	return *this;
}

Executor &Executor::inputBody() {
	char buf[5];
	bzero(buf, 5);
	int len = 0;
	while ((len = read(fdOut[0], buf, 4)) > 0)
	{
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
