#pragma once

#include <string>

// Forward declaration of PostState and std::string, so that Post can compile
class PostState;

// The Context class
class Post 
{
    // For allowing PostState concrete classes to access changeState()
    friend class PostState;

    // The actual content of the post
    std::string m_content{};
    
    // The private State object pointer
    PostState* m_postState{};

    // Function to change the state
    void changeState(PostState* postState);

public:
    Post();

    // State dependent functions
    // We delegate the state based functionality to the respective state objects
    void viewContent();

    void addContent(std::string& content);

    void reviewContent(bool isPassing);

    // Destructor
    ~Post();

};
