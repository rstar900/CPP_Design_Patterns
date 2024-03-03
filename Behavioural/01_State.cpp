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
    ~Post()
    {
        delete m_postState;
    }

};


// The State classes

class Draft final: public PostState
{
    // overrides
protected:
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
    // overrides
protected:
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
    // overrides
protected:
    virtual void viewContent();
    virtual void addContent(std::string& content);
    virtual void reviewContent(bool isPassing);

public:
    // Contructor
    Published()
    {
       std::cout << "[Published State:] Welcome!" << std::endl;
    }
};


// ---- PostState changeState functions implementation Start ----

void PostState::changeState(PostState* postState)
{
    m_post->changeState(postState);
}

std::string& PostState::getContent()
{
    return m_post->m_content;
}

// ---- PostState functions implementation End ----


// ---- Post public function Implementations starts ----

Post::Post() 
{
    // Set initial state to be Draft
    m_postState = new Draft();
    m_postState->setContext(this);
}

void Post::changeState(PostState* postState)
{
    if (m_postState != nullptr)
    {
        delete m_postState; 
    }
    m_postState = postState;
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

void Draft::viewContent()
{
    std::cout << "[Draft State:] Cannot view post yet." << std::endl;
}

void Draft::addContent(std::string& content)
{
    std::cout << "[Draft State:] Added content, changing to InReview state..." << std::endl;
    getContent().append(content);
    changeState(new InReview());
}

void Draft::reviewContent(bool isPassing)
{
    std::cout << "[Draft State:] Cannot review post yet." << std::endl;
}

// ---- Draft function implementations End ----


// ---- InReview function implementations Start ----

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
        changeState(new Published());
    }
    else
    {
        std::cout << "[InReview State:] Review unsuccessful, changing back to draft state..." << std::endl;
        changeState(new Draft());
    }    
}

// ---- InReview function implementations End ----


// ---- Published function implementations Start ----

void Published::viewContent()
{
    std::cout << "[Published State:] " << getContent() << std::endl;
}

void Published::addContent(std::string& content)
{
    std::cout << "[Published State:] Cannot edit post unless in Draft state." << std::endl;
}

void Published::reviewContent(bool isPassing) 
{
    std::cout << "[Published State:] Cannot review post after publishing." << std::endl;
}

// ---- Published function implementations End ----


int main()
{
    Post post;
    std::string content{"Hello from published post"};
    
    post.addContent(content);
    post.viewContent();

    post.reviewContent(false);
    post.reviewContent(true);
    
    std::string content_addition{"\nSome more additions"};
    post.addContent(content_addition);
    post.viewContent();

    post.reviewContent(true);

    post.addContent(content_addition);
    post.reviewContent(false);
    post.viewContent();
}
