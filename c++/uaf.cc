#include <iostream>
#include <cstring>

using namespace std;

class AuthenticationToken {
private:
  char passwd[20];
  int  loggedIn;
  
public:
  AuthenticationToken(char *pwd)
    : loggedIn(1)
  {
    strncpy(passwd, pwd, 20); // Copies at *most* 20 characters, so it
                              // doesn't overflow the buffer
  }

  void setLoggedOut() { loggedIn = 0; }
  int  getLoggedIn() { return loggedIn; }
};

int main() {
  string s;
  AuthenticationToken *token = new AuthenticationToken("thepassword");
  char *secret = strdup("initial secret");

  cout << "Type commands `logout`, `getsecret`, or `setsecret <secret>`\n";
  while (getline()) {
    cout << "Address of secret is " << static_cast<void *>(secret) << endl;
    cout << "Address of auth token is " << token << endl;
    cout << "User typed in " << s;
    if (strcmp(s,"logout\n") == 0) {
      token->setLoggedOut();
      delete token;
      cout << "You are now logged out!" << endl;
    } else if (strncmp(s, "setsecret ", 10) == 0) {
      // String begins with "setsecret"
      char *oldsecret = secret;
      secret = strdup(s);
      delete oldsecret;
      cout << "Secret now set at " << static_cast<void *>(secret) << endl;
    } else if (strcmp(s,"getsecret\n") == 0) {
      if (!token->getLoggedIn()) {
        cout << "You are logged out, no secret for you..." << endl;
      } else {
        cout << "The secret is\n" << secret << endl;
      }
    }
  }
}
