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

#include "post.h"

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

    return 0;
}