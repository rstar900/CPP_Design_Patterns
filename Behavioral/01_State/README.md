# State Pattern
A good description at https://refactoring.guru/design-patterns/state
<br>
In short, it replaces the classical switch case and if statements for states within the same function by replicating this function (but with state related functionality) across multiple state objects and delegating the responsibility to those states objects for handling that function.
## TODO: Description of files
## Build and Run
Execute the following commands:
```
g++ main.cpp post.cpp post_state.cpp -o main
```

```
./main
```
