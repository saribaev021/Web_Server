#ifndef WEB_SERVER_EXECUTOR_HPP
#define WEB_SERVER_EXECUTOR_HPP

#include <list>
#include <iostream>
#include <unistd.h>
#include <vector>

class Executor{
private:
	char **arrayEnv;
	std::string _launcher;
	std::string scrypt;
	int fdIn[2];
	int fdOut[2];
	std::string body;
public:
	Executor(char **arrayEnv, const std::string &launcher, const std::string &scrypt, const std::string& body):
	arrayEnv(arrayEnv), _launcher(launcher), scrypt(scrypt), body(body) {
	}

	char **getArrayEnv() const {
		return arrayEnv;
	}
	const std::string &getLauncher() const {
		return _launcher;
	}
	const std::string &getScrypt() const {
		return scrypt;
	}

	Executor &launcher();
	Executor &putBody();
	Executor &inputBody();

	static void changeFd(int *fd);

	void changeFdIn();
	void changeFdOut();
	void pipeFd();
	void closeFd();

	const std::string &getBody() const;
	char **getLauncherArray();
};

Executor &Executor::launcher() {
	int status = 0;

	pid_t pid = fork();
	close(fdIn[1]);
	if (pid == 0){
		dup2(fdIn[0], 0);
		dup2(fdOut[1], 1);
		status = execve(getLauncherArray()[0], getLauncherArray(), arrayEnv);
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
	}
	return *this;
}

Executor &Executor::inputBody() {
//	char *line;
//	body.clear();
//	while (Gnl::get_next_line(&line, fdOut[0]) > 0){
//		body += std::string(line);
//		write(2, "#", 1);
//	}
//	return *this;

	std::string message;
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

void Executor::closeFd() {
	close(fdIn[0]);
	close(fdIn[1]);
	close(fdOut[0]);
	close(fdOut[1]);
}

void Executor::changeFd(int *fd) {
	dup2(fd[0], 0);
	dup2(fd[1], 1);
}

void Executor::changeFdIn() {
	dup2(fdIn[0], 0);
}

void Executor::changeFdOut() {
	dup2(fdOut[1], 1);
}

const std::string &Executor::getBody() const {
	return body;
}

char **Executor::getLauncherArray() {
	char **array = (char**)malloc(sizeof(char*) * 3);
	array[0] = strdup(_launcher.c_str());
	array[1] = strdup(scrypt.c_str());
	array[2] = NULL;
	return array;
}



#endif //WEB_SERVER_EXECUTOR_HPP
