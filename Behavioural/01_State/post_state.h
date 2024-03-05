#pragma once

#include <iostream>

// Forward declaration of Post class, so that PostState recognizes it
class Post;

// The State abstract class
class PostState
{

    // Declare Post to be a friend class to be able to change Context for PostState concrete objects
    friend class Post;

protected:
    // Keep the Post pointer as protected in abstract class itself
    Post* m_post{};

    // function to set Context
    void setContext(Post* post)
    {
        m_post = post;
    }

    // Function to change state of Post object
    void changeState(PostState* post);

    // Function to access content of Post
    std::string& getContent();

    // State dependent functions
    virtual void viewContent() = 0;
    virtual void addContent(std::string& content) = 0;
    virtual void reviewContent(bool isPassing) = 0;

public:
    // Virtual destructor
    virtual ~PostState() = default;
    
};

//---- Concrete States ----

class Draft final: public PostState
{
    // overrides
protected:
    virtual void viewContent() override;
    virtual void addContent(std::string& content) override;
    virtual void reviewContent(bool isPassing) override;

public:
    // Contructor
    Draft();
    
};

class InReview final: public PostState
{
    // overrides
protected:
    virtual void viewContent() override;
    virtual void addContent(std::string& content) override;
    virtual void reviewContent(bool isPassing) override;

public:
    // Contructor
    InReview();
    
};

class Published final: public PostState
{
    // overrides
protected:
    virtual void viewContent();
    virtual void addContent(std::string& content);
    virtual void reviewContent(bool isPassing);

public:
    // Contructor
    Published();
};