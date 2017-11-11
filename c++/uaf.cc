// Use after free exploit
// See video on my blog to understand how this works.
// For fix: uncomment lines with fix: in front of them.
#include <iostream>
#include <cstring>

using namespace std;

class AuthenticationToken {
private:
  char passwd[20]; // A fixed size password
  int  loggedIn;   // A flag saying whether or not I'm logged in
  
  // password[0]  
  // ...
  // password[19]
  // loggedIn[0]
  // loggedIn[1]
  // loggedIn[2]
  // loggedIn[3]

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

  while (getline(cin,s)) {
    cout << "Address of secret is " << static_cast<void *>(secret) << endl;
    cout << "Address of auth token is " << token << endl;
    cout << "User typed in " << s << endl;
    if (s == "logout") {
      token->setLoggedOut();
      delete token;
      /* fix: token = NULL; */
      cout << "You are now logged out!" << endl;
    } else if (s.compare(0,10, "setsecret ") == 0) {
      // String begins with "setsecret"
      char *oldsecret = secret;
      string substr = s.substr(10, s.size());
      secret = strdup(s.c_str());
      delete oldsecret;
      cout << "Secret now set at " << static_cast<void *>(secret) << endl;
    } else if (s =="getsecret") {
      if (/* fix: !token || */ !token->getLoggedIn()) {
        cout << "You are logged out, no secret for you..." << endl;
      } else {
        cout << "The secret is\n" << secret << endl;
      }
    }
  }
}
