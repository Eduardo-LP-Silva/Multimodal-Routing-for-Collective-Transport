# Multimodal-Routing-for-Collective-Transport

This is a project developed in the course "Algorithm Design and Analysis" (CAL) at FEUP. It it designed to simulate a service wich provides the users with the best path from one point to another (in a city for example), taking into account various aspects such as time, distance and expenditure between different modes of transportation.

## Overview

When starting the application, the user is presented with the start up menu in which he can choose which environment (graph) he wants to work with, either with a real data map (option 1) or with a test one (option 2).

![screenshot_1](https://user-images.githubusercontent.com/32617691/42137236-c8a5d95e-7d60-11e8-919a-5661bf7dc898.png)

The next set of choices is equal in both environments, the difference between them being in the map used:

1. Experimental Graph (Real Data) - Here the map will be generated using real data taken from https://www.openstreetmap.org of a portion of the city of Porto. This data was converted in .txt files using a combination of two C# parsers, one of them provided by João Carvalho (@jflcarvalho). However, some "artificial" data had to be created for better visualization of the results. This data consists of additional pedestrian paths connectingthe subway to near regular paths.

![image](https://user-images.githubusercontent.com/32617691/42137377-281a3324-7d63-11e8-8c8b-ef67da61a685.png)

2. Custom Test Graph - This a much smaller, "handmade" graph created for testing purposes only.

![image](https://user-images.githubusercontent.com/32617691/42137410-7cdb5a82-7d63-11e8-8221-e3f5b6a7b3e4.png)

3. Exit - The application will terminate.

Selecting any of the first two options will bring up the respective map in a new window. The user can move around the map by left clicking anywhere and dragging the mouse. He can also zoom in and out with mouse wheel.   

**Note:** From here on out, we will be using the first option since it is the most interesting one.  

In the graphviewer window, each node is represented by a yellow dot (with a small '.' tag above) and each edge by a colored line connecting two nodes. Each edge color indicates a different mean of transportation:

* Red - Pedestrian path/road.
* Green - Subway.
* Blue - Bus route.

**Note:** In this graph, we do not differentiate between one way or two way paths for simplicity. Also, keep in mind that, although unrealistic, the bus routes connecting each pair of nodes are not considered as roads as well so as to give a better visualization of the results.

### Main Menu

![image](https://user-images.githubusercontent.com/32617691/42137507-5103a764-7d65-11e8-9212-fb08ff68da98.png)

This menu gives the user the option to calculate a new route or to exit the application.

### Route Calculation

![image](https://user-images.githubusercontent.com/32617691/42137550-1e7c254a-7d66-11e8-8ba6-084ea5efb1b9.png)

If the user chooses the firs option, he will be propted to pick the origin point. He can do this by indicating the street name or the ID of the node. In the experimental graph it is recommended to choose the firt option and in the test one the second option (in the test graph the nodes have their ID above them. This was not done in the experimental graph so as not to clutter the map).  
If the user picked an origin point by its street name, he will be given the choice to execute an exact or approximate search of that name.

![image](https://user-images.githubusercontent.com/32617691/42137587-c561bff0-7d66-11e8-8fd6-6e6c4ae37843.png)

1. Exact Search - The application will search for names that are equal to or contain the string given using the **Knuth-Morris-Pratt**'s algorithm.
2. Approximate Search - The application will search for similar names to the one given.

After that, the user can choose to list all the results returned or just a top 5 of the most accurate ones (recommended option) ordered by similarity. 

![image](https://user-images.githubusercontent.com/32617691/42137614-5550a914-7d67-11e8-8c20-07160f50d4d8.png)

He should then choose one of the results.

![image](https://user-images.githubusercontent.com/32617691/42137637-b4289834-7d67-11e8-821f-faf960eb2c78.png)

After that, the user will be prompted to pick a destination in the same fashion.

![image](https://user-images.githubusercontent.com/32617691/42137647-e0d64930-7d67-11e8-8f51-4c8476d4f734.png)

After both points are sucessfully picked, the user can choose which path suits him the best:

![image](https://user-images.githubusercontent.com/32617691/42137654-2d3fac3a-7d68-11e8-9cbc-cd686958a2f0.png)

1. Shortest Path - The application will only take in consideration the distance between each node, returning the shortest path between the origin and destination.

2. Best Path - By choosing this option, the app will take into account not only the distance between each node but also the walking distance, reaching a balance between the two.

3. Quickest Path - Here the app will only take into consideration the time that it takes to travel between each node, minimizing the overall time it takes to travel from the origin to the destination.

**Note:** All public transports have a 2 minute waiting time associated.

After choosing one of these options, the user can customize his path based on another set of attributes:

![image](https://user-images.githubusercontent.com/32617691/42137750-0409529c-7d6a-11e8-84b6-d0cd03d6f83f.png)

1. Transport Preferences - The user can indicate his prefered transportation method: bus or subway.

![image](https://user-images.githubusercontent.com/32617691/42137785-8299515c-7d6a-11e8-9af7-2974485d2361.png)

2. Spending Limit - The user can set a maximum amount of money he can spend. The pre-defined price is of 1.20€/hour (just like in the city of Porto).

After setting everything up (or not), the user can choose the 3rd option to calculate the path. The results are computed using highly customized versions of **Dijkstra's algorithm** and are shown in two different ways:

1. In the console window, through text indications. Here it also present the time it takes to traverse each different section of the path (sections are delimited by different transportation methods).

![image](https://user-images.githubusercontent.com/32617691/42137956-20f3716e-7d6d-11e8-9221-ef95c7aff6bb.png)

2. In the graphviewer window. The origin node is represented in blue, the destination in black and the path nodes in green. Each of these nodes is also increased in size.

![image](https://user-images.githubusercontent.com/32617691/42137963-38e7c5d6-7d6d-11e8-9db3-ff4e407bf3a1.png)

The user is then returned to the main menu.

## Usage

### Source Files

After cloning the repo, in order to compile the project, you'll need to set your character set to "**Not** set" or something similar. Also, you'll need to include the ws2_32 library in the project.

### Executable

To use only the executable, you only need to make sure the .exe is in the same folder as the text files and the graphviewer.jar. After that just run it like any other executable.





