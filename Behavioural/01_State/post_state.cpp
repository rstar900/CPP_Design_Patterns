#include "post_state.h"
#include "post.h"

// ---- PostState changeState() and getContent() functions implementation Start ----

void PostState::changeState(PostState* postState)
{
    m_post->changeState(postState);
}

std::string& PostState::getContent()
{
    return m_post->m_content;
}

// ---- PostState changeState() and getContent() functions implementation End ----



// ---- Draft function implementations Start ----

Draft::Draft()
{
    std::cout << "[Draft State:] Welcome!" << std::endl;
}

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

InReview::InReview()
{
    std::cout << "[InReview State:] Welcome!" << std::endl;
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

Published::Published()
{
    std::cout << "[Published State:] Welcome!" << std::endl;
}

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