/* 
 * File:   SignIn.h
 * Author: Josh Carlito
 *
 * Created on March 20, 2023, 8:15 PM
 */

#ifndef SIGNIN_H
#define SIGNIN_H
#include "StoreFront.h"

class SignIn {
private:
    // Admin key necessary for creating an admin account
    const int adminKey = 1234;
    // Declare Variables
    UserInfo information; // Username and Password
    fstream binarySignInFile; // file SignIn info is being written to
    char userInput; // User input to navigate the sign-in class
    bool exitSignIn = false; // Flag on when to end the sign-in process

    /********************
     * Helper functions *
     ********************/
    void toLowercase();
    void setUserInput(); // Set user input
    // Display options for a user after an error message
    void displayOptions();
public:
    // Constructor
    SignIn();
    // Destructor
    ~SignIn();

    /*********************
     * Mutator functions *
     *********************/
    void setUsername(); // Set username
    void setPassword(); // Set password
    void setAdminFlag(); // Set admin flag to distinguish between accounts

    void setExitSignIn(bool flag) // Set exit sign-in flag
    {
        exitSignIn = flag;
    }

    /**********************
     * Accessor functions *
     **********************/

    bool getExitSignIn() const {
        return exitSignIn;
    }

    char getUserInput() const {
        return userInput;
    }

    string getUsername() {
        return information.username;
    }

    bool getAdminStatus() const {
        return information.adminFlag;
    }

    /******************
     * Misc functions *
     ******************/

    // Validate user's admin key
    void validateAdminKey();

    // Write user information to a binary file
    void writeBinary();

    // Validate user sign-in information
    void validateUser();

    // Check if user is trying to make a duplicate username
    bool duplicateUsername();

    // Display opening sign-in prompt 
    void displayMenu();

    // Display an error message if username/password are invalid
    void displayError();

    // Display user's information
    void displayUserInfo();
};

#endif /* SIGNIN_H */