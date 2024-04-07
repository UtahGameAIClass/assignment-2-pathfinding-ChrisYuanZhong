# EAE6610: Assignment2-PathFinding

## Instructions
Your task for this assignment is to explore some of the pathfinding algorithms we discussed in class. Working alone and using openFrameworks (http://openframeworks.cc), your task is to implement the algorithms described below and analyze your results in a 3-5 page writeup. Note that for some of these tasks, you will be integrating your new solutions with your code from Assignment 1. You will submit your code via [our Github Classroom portal] by ensuring that your code is **pushed to your repository by the assignment deadline**. You will also hand in a 1 to 2-page [process letter](#About-Ungrading-and-Process-Letters) placed in the top-level directory of your git repository.

You are expected to follow Google’s C++ Style Guide for your code. It is available here: https://google.github.io/styleguide/cppguide.html

This is an individual assignment; you are to work alone. As always, you are expected to abide by the University of Utah Code of Conduct, explicitly outlined in the class syllabus, which includes providing appropriate attribution for all external sources of information consulted while working on this assignment.

### Overview
1. [Setup](#Setup)
2. [Assignment Deliverables](#assignment-deliverables)
    1. [First Steps](#first-steps15-points)
    2. [Dijkstra’s Algorithm, A*](#dijkstras-algorithm-a-25-points)
    3. [Heuristics](#heuristics-05-points)
    4. [Putting It All Together](#putting-it-all-together-4-points)
    5. [Process Letter](#process-letter)

### Setup
Before you are able to get started with the assignment, go to [SETUP.md](SETUP.md) and configure your working environment. Also, add the Assignment 1 project into this repository to continue working on top of that for the Assignment 2.

### Assignment Deliverables

#### First Steps(1.5 Points)
Create two graphs that you will use for your experiments. Both graphs should be a weighted singly-connected digraph. Remember, only use positive weights.

Your first graph should represent something meaningful in the world. Perhaps a roadmap of Salt Lake City or your hometown, the EAE building, etc. Your choice of what you represent is up to you; read ahead to figure out how to maximize your work effort. This graph should be large enough so that you can learn some interesting things about the algorithms, but small enough to enable efficient computation in your experiments. As a rule of thumb, 10 vertices is probably too few, but 50 is likely too many.

Your second graph should be designed to test the limits of the algorithms. It should be Very Big™. You can generate it randomly, find a graph somewhere on the internet (make sure you cite where), or try to generate it using some data set of your choosing. One thing is for sure: you should not author this graph by hand. As a rule of thumb, you should be targeting graphs with thousands or tens-of-thousands of vertices and edges. In your writeup, include a description of both graphs. What does the first one represent? How did you create the second one?

#### Dijkstra’s Algorithm, A* (2.5 Points)
Your next task is to implement both Dijkstra’s Algorithm and the A* Algorithm. I suggest you get them both working on your first graph before you begin testing on your second graph. For A*, pick a simple heuristic like a constant guess or some form of Manhattan Distance. If your large graph doesn’t have any meaningful distance or way to compute a heuristic, use a random one or constant guess. What you choose isn’t too important for this section of the assignment.

Compare and contrast the performance of the two algorithms on both of your graphs in terms of runtime, number of nodes visited, and memory used. What else can you say about these algorithms? What effects does the graph structure have on performance? You are expected to present data in your writeup to support your analysis.

#### Heuristics (0.5 Points) 
Looking solely at the A* algorithm, design and implement at least two heuristics for your first graph. The heuristics you used in the previous portion of the assignment can count as one of these two. A few options are: random, hand-authored, Manhattan distance, constant guess, or Euclidian distance. These are not the only possibilities; consider others! These heuristics need not work on your second, larger graph.

Describe each of your heuristics in detail. Is it admissible? Consistent? Overestimating? Underestimating? What happens to the performance of the A* algorithm when you use different heuristics? Again, present data in your writeup to support your analysis.

#### Putting It All Together (4 Points)
Combine your pathfinding algorithms with the appropriate algorithms from Homework 1. Design an “indoor environment” that contains a number of obstacles for your character to avoid. Using a principled technique of your choosing (i.e. a division scheme we discuss in class or a set of rules you use to represent the space manually), create a graph representation of that environment and use it to perform pathfinding. You should be able to click anywhere in the window, have that click location be quantized into the graph and have your A* algorithm compute an efficient path to that location. Have your character follow the computed path.

> [!TIP]
> Although more computationally intensive, having a dense graph can avoid the need for obstacle avoidance in your movement. Videos or screenshots (with breadcrumbs) of your character in action are a must.

#### Process Letter
Now that you have implemented and evaluated a number of algorithms write a 3-5 page paper summarizing your findings. We strongly recommend that you do not limit yourself to only answering those questions posed in this assignment. Think creatively about what you have done. What other parameters can you tweak and what effect do they have on the results? 

> [!TIP]
> The most successful write-ups will contain evidence that you have thought deeply about these algorithms and have gone beyond what is written in the assignment: comment not on what you have done, instead comment on what you have learned and how you have learned it!

Place a PDF of your letter in the assignment folder within `apps/myApps/`. That is, if your assignment folder is called `gameAI`, then place your letter at `apps/myApps/gameAI/letter.pdf`

##### Formatting for your Process Letter
Your paper must be formatted with the ToDIGRA submission template, available here: http://todigra.org/index.php/todigra/about/submissions. Please name your writeup file per the following convention: [last name]_assignment[number]_report.pdf

##### About Ungrading and Process Letters
This class is [ungraded](https://www.jessestommel.com/ungrading-an-faq/).

Classes that use the ungrading technique ask students to write about their learning process *as it happens*, and instructors offer feedback focused on meeting course learning goals. Your learning journey is unique to you, and un-grading allows us as a class to decouple grades from what ultimately matters in this class: that you actually *learn*.

A process letter is a letter you will write to the teaching staff where you will reflect on your own progress and learning as it has happened for the respective assignment. 

To help you draft one, imagine someone is creating a documentary of you as you complete the tasks in this assignment. Now, imagine that you're looking at this documentary of yourself and you have to answer the following questions:
- what would you say about yourself? 
- what would you say that you knew at the end that you didn't know at the beginning?
- would you say that you had fun?
- did you find the assignment challenging?
- did you find the assingment useful? not useful? and for either one: why?
- have you become curious about anything new?
- did you feel what you did was related to the class content?
- do you think what you did is relevant to your class project?
- what have you not done yet that you have seen in other games?

#### Submission Instructions
By the deadline stated on the syllabus, please provide a link to a Github or Gitlab repository that we can access to grade. The repository should contain all of your code (including the openFrameworks library itself), and should also contain your process letter in .pdf format.

Your repository must include a README text/Markdown file containing a description of how to run your code, as well as where to find the source code relevant to each of the sections identified above, as well as any special instructions we need to consider to run your code.

## Rubric
> [!IMPORTANT]
> As mentioned in the class syllabus, this class is entirely based on the process letters. However, to help you get a sense of your own mastery within the assignment, all assignments will be *virtually* graded according to a rubric. Your virtual grade has **nothing** to do with your official standing or grade in the course; it is simply a reflection of your proficiency within this assignment, and you should use it to calibrate how close you are to meeting the learning objectives of this course, which is what we truly care about.

### First Steps (1.5 Points).
- (0.5)	First (small) Graph created.
- (1.0)	Second (large) Graph created with more than 1000 nodes.
  
### Dijkstra’s Algorithm, A* (2.5 Points). 
- (1.0)	Dijkstra’s Algorithm created.
- (1.0)	A* Algorithm created.
- (0.5)	Simple heuristic created.

### Heuristics (0.5 Point).
- (0.5)	Second heuristic created for second graph.

### Putting It All Together (4.0 Points).
- (0.5)	Indoor environment is designed.
- (1.0)	Abstraction scheme is implemented.
- (1.0)	Boid performs A* Pathfinding to a click.
- (0.5)	Boid performs Pathfollowing on the computed path.
- (1.0)	Pathfinding/Pathfollowing “looks good:” the Boid does not touch the walls at all.

### The Walls Are Lava™ (Variable multiplier). If the Boid does touch the wall during pathfinding, the score is slightly reduced:
- If the Boid has little overlap with walls, your score will be multiplied by 0.95.
- If the Boid has moderate overlap with walls, your score will be multiplied by 0.85.
- If the Boid has significant overlap with walls, your score will be multiplied by 0.75.

### Process Letter (6.0 Points).
- (0.25) First Steps questions posed in the assignment are answered.
- (0.25) First Steps is illustrated with screenshots.
- (1.0)	Dijkstra’s Algorithm, A* questions posed in the assignment are answered.
- (0.5)	Dijkstra’s Algorithm, A* is illustrated with screenshots.
- (1.0)	Dijkstra’s Algorithm, A* discussion contains something unique (beyond what the assignment asks).
- (1.5)	Heuristics questions posed in the assignment are answered.
- (1.0)	Heuristics analysis is presented with supporting data.
- (0.5)	Putting It All Together is presented with supporting screenshots.

## Multipliers

### Codebase Style
- No README (×0 multiplier). The Github / Gitlab repository does not have a README file.
- Does Not Compile / Build (×0 multiplier). The code submission does not compile per the instructions on the README.
- C++ Coding Style not followed (Variable multiplier). The code does not follow Google’s C++ Style guide, per: https://google.github.io/styleguide/cppguide.html
    - If you deviate >5 times, your score for that portion will be multiplied by 0.95.
    - If you deviate >10 times, your score for that portion will be multiplied by 0.85.
    - If you deviate >15 times, your score for that portion will be multiplied by 0.75.
 
### Writeup Style
- Format (×0 multiplier). The writeup does not adhere to the ToDIGRA submission template, available here: http://todigra.org/index.php/todigra/about/submissions. Note: you are not submitting this for anonymous review. :)
- Page Count (Variable multiplier). Your writeup must hit at least 3 pages of content. If you have less than 3, then the writeup score will be multiplied by (n / 3), where n is the teaching staff’s estimate of how much page content you have.
- Spelling and Grammar (Variable multiplier). Having proper grammar and spelling is important and difficult. If you are having trouble, ask for help from your classmates or the university writing center.
    - If you have 1-3 grammar/spelling mistakes, your score will be multiplied by 0.95.
    - If you have 4-6 grammar/spelling mistakes, your score will be multiplied by 0.85.
    - If you have 7+ grammar/spelling mistakes, your score will be multiplied by 0.75.


