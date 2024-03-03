// Context class -> object that should act differently based on different states
// Consider a Post object (Context) which has states : Draft, InReview, and Published
// One should be able to only view the contents of the post in Published state 
// So, the viewContent(), addContent() and reviewContent() functions behave differently based on the state of Post
// The state is managed by independent State objects (classes deriving PostState interface in this case)
// The addContent() function should allow adding post content in Draft state only
// The viewContent() function should only work in Published state
// The reviewContent() function takes in a boolean representing whether to pass or fail the review and works only in InReview state
// If the review fails, the Post object goes back into draft state, else Published

// Inspiration taken from https://refactoring.guru/design-patterns/state
// And https://refactoring.guru/design-patterns/state/cpp/example
// And https://doc.rust-lang.org/book/ch17-03-oo-design-patterns.html

// TODO: Optimizations for setContext() and bring the Published State methods out for uniformity

#include <iostream>

// Forward declaration of Post class, so that PostState recognizes it
class Post;

// The State interface
class PostState
{

    // Private Context pointer will be in concrete States
    // Also declare Post to be a friend class in concrete States as well
    friend class Post;

protected:
    // function to set Context
    virtual void setContext(Post* post) = 0;

    // State dependent functions
    virtual void viewContent() = 0;
    virtual void addContent(std::string& content) = 0;
    virtual void reviewContent(bool isPassing) = 0;

public:
    // Virtual destructor
    virtual ~PostState() = default;
    
};

// The Context class
class Post 
{
    // To allow state objects to change internal state of the post object
    friend class Draft;
    friend class InReview;
    friend class Published;

    // The private State object pointer
    PostState* m_postState{};

    // The actual content of the post
    std::string m_content{};

    // Private function to change the state
    void changeState(PostState* postState)
    {
        if (m_postState != nullptr)
        {
            delete m_postState; 
        }
        m_postState = postState;
        m_postState->setContext(this);
    }

public:
    Post();

    // State dependent functions
    // We delegate the state based functionality to the respective state objects
    void viewContent();

    void addContent(std::string& content);

    void reviewContent(bool isPassing);

    // Destructor
    ~Post()
    {
        delete m_postState;
    }

};


// The State classes

class Draft final: public PostState
{
    // To allow post objects to change the internal context
    friend class Post;

    // Private Context pointer
    Post* m_post{};

    // overrides
protected:
    void setContext(Post* post);
    virtual void viewContent() override;
    virtual void addContent(std::string& content) override;
    virtual void reviewContent(bool isPassing) override;

public:
    // Contructor
    Draft()
    {
       std::cout << "[Draft State:] Welcome!" << std::endl;
    }
    
};

class InReview final: public PostState
{
    // To allow post objects to change the internal context
    friend class Post;

    // Private Context pointer
    Post* m_post{};

    // overrides
protected:
    void setContext(Post* post);
    virtual void viewContent() override;
    virtual void addContent(std::string& content) override;
    virtual void reviewContent(bool isPassing) override;

public:
    // Contructor
    InReview()
    {
       std::cout << "[InReview State:] Welcome!" << std::endl;
    }
    
};

class Published final: public PostState
{
    // To allow post objects to change the internal context
    friend class Post;

    // Private Context pointer
    Post* m_post{};

    // overrides
protected:
    void setContext(Post* post)
    {
        m_post = post;
    }
    virtual void viewContent() override
    {
        std::cout << "[Published State:] " << m_post->m_content << std::endl;
    }
    virtual void addContent(std::string& content) override
    {
        std::cout << "[Published State:] Cannot edit post unless in Draft state." << std::endl;
    }
    virtual void reviewContent(bool isPassing) override
    {
        std::cout << "[Published State:] Cannot review post after publishing." << std::endl;
    }

public:
    // Contructor
    Published()
    {
       std::cout << "[Published State:] Welcome!" << std::endl;
    }
};

// ---- Post public function Implementations starts ----

Post::Post() 
{
    // Set initial state to be Draft
    m_postState = new Draft();
    m_postState->setContext(this);
}

void Post::viewContent()
{
    m_postState->viewContent();
}

void Post::addContent(std::string& content)
{
    m_postState->addContent(content);
}

void Post::reviewContent(bool isPassing)
{
    m_postState->reviewContent(isPassing);
}

// ---- Post public function Implementations Ends ----


// ---- Draft function implementations Start ----

void Draft::setContext(Post* post)
{
    m_post = post;
}

void Draft::viewContent()
{
    std::cout << "[Draft State:] Cannot view post yet." << std::endl;
}

void Draft::addContent(std::string& content)
{
    std::cout << "[Draft State:] Added content, changing to InReview state..." << std::endl;
    m_post->m_content.append(content);
    m_post->changeState(new InReview());
}

void Draft::reviewContent(bool isPassing)
{
    std::cout << "[Draft State:] Cannot review post yet." << std::endl;
}

// ---- Draft function implementations End ----


// ---- InReview function implementations Start ----

void InReview::setContext(Post* post)
{
    m_post = post;
}

void InReview::viewContent()
{
    std::cout << "[InReview State:] Cannot view post yet." << std::endl;
}

void InReview::addContent(std::string& content)
{
    std::cout << "[InReview State:] Cannot edit post unless in Draft state." << std::endl;
}
 
void InReview::reviewContent(bool isPassing)
{
    if (isPassing) 
    {
        std::cout << "[InReview State:] Review successful, changing to Published state..." << std::endl;
        m_post->changeState(new Published());
    }
    else
    {
        std::cout << "[InReview State:] Review unsuccessful, changing back to draft state..." << std::endl;
        m_post->changeState(new Draft());
    }    
}

// ---- InReview function implementations End ----

int main()
{
    Post post;
    std::string content{"Hello from published post"};
    
    post.addContent(content);
    post.viewContent();

    post.reviewContent(false);

    std::string content_addition{"\nSome more additions"};
    post.addContent(content_addition);
    post.viewContent();

    post.reviewContent(true);
    post.viewContent();
}
