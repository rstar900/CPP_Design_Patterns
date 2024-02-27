// Context class -> object that should act differently based on different states
// Consider a Post object (Context) which has states : Draft, InReview, and Published
// One should be able to only view the contents of the post in Published state 
// So, the viewContent() function behaves differently based on the state of Post
// Also, the addContent() function should allow adding post in Draft state only
// There should be a public function so that an admin can review and change the state either to Draft (failiure) or Published

// Inspiration taken from https://refactoring.guru/design-patterns/state
// And https://doc.rust-lang.org/book/ch17-03-oo-design-patterns.html

#include <iostream>

// The State interface
class PostState
{

    // To allow post objects to change the internal context
    friend class Post;

    // Private Context pointer will be in concrete States 

protected:
    // function to set Context
    virtual void setContext(Post* post) = 0;

    // State dependent functions
    virtual void viewContent() = 0;
    virtual void addContent(std::string& content) = 0;
    virtual void reviewContent() = 0;

public:
    // Virtual destructor
    virtual ~PostState() = default;
    
};

// The State classes

class Draft final: public PostState
{
    // Private Context pointer
    Post* m_Post{};

    // overrides
protected:
    void setContext(Post* post)
    {
        m_Post = post;
    }
    virtual void viewContent() override
    {
        // TODO
    }
    virtual void addContent(std::string& content) override
    {
        // TODO
    }
    virtual void reviewContent() override
    {
        // TODO
    }
    
};

class InReview final: public PostState
{
    // Private Context pointer
    Post* m_Post{};

    // overrides
protected:
    void setContext(Post* post)
    {
        m_Post = post;
    }
    virtual void viewContent() override
    {
        // TODO
    }
    virtual void addContent(std::string& content) override
    {
        // TODO
    }
    virtual void reviewContent() override
    {
        // TODO
    }
    
};

class Published final: public PostState
{
    // Private Context pointer
    Post* m_Post{};

    // overrides
protected:
    void setContext(Post* post)
    {
        m_Post = post;
    }
    virtual void viewContent() override
    {
        // TODO
    }
    virtual void addContent(std::string& content) override
    {
        // TODO
    }
    virtual void reviewContent() override
    {
        // TODO
    }
    
};

// The Context class
class Post 
{
    // To allow state objects to change internal state of the post object
    friend class PostState;

    // The private State object pointer
    PostState* m_postState{};

    // Private function to change the state
    void changeState(PostState* postState)
    {
        if (m_postState != nullptr)
        {
            delete m_postState; 
        }
        this->m_postState = postState;
        m_postState->setContext(this);
    }

public:
    Post() 
    {
        // Set initial state to be Draft
        m_postState = new Draft();
        m_postState->setContext(this);
    }

    // State dependent functions
    // We delegate the state based functionality to the respective state objects
    void viewContent()
    {
        m_postState->viewContent();
    }

    void addContent(std::string& content)
    {
        m_postState->addContent(content);
    }

    void reviewContent()
    {
        m_postState->reviewContent();
    }

};
