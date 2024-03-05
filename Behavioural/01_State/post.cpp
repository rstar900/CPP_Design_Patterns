#include "post.h"
#include "post_state.h"

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

// Destructor
Post::~Post()
{
    delete m_postState;
}

// ---- Post public function Implementations Ends ----