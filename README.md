# Resource-Area-Optimization-Project
Project Developers:
Eyüp Ensar kara | Yunus Hanifi Öztürk

Project Instructions


A company carrying out offshore natural resource exploration and extraction operations
the search area with the right number and optimal dimensions in order to obtain maximum profit
to subdivide the land into divided areas (parcels). For this purpose, according to certain rules
the most appropriate area partitioning process together with cost-benefit calculations and
development of a software that creates a visual map of segmented search areas
is expected.
Objective: The project aims to develop students' knowledge of basic programming and graph drawing.
reinforcement and development of problem solving skills.
Programming Language: The project will be implemented using C programming language.
The project consists of two main phases as detailed below.
PHASE 1:
The first phase of the project constitutes the seismic survey leg of the resource exploration company. This includes
The area of the closed figure formed by joining the given coordinate points according to the source reserve
will correspond to 1/10 of the amount. For this, the following steps
should be applied:
Step 1: From the web page on a url link to be shared from e-support, a different number of
Reading the (x,y) coordinate values of the points
Step 2: Linear combination of these read points according to the order given 2
Drawing the shape of a dimensional closed area
Step 3: Calculating the surface area value of the drawn shape and multiplying this value by 10
the process of obtaining the resource reserve value should be carried out. (Surface area
calculation, the total sum of all unit squares that the figure passes over and covers
by finding the number or by calculating the mathematical area to be used
Both methods are preferable).
Where (0,0) corresponds to the upper left corner of the initial coordinate values in the plotted plane.
and the x value increases as you move to the right and the y value increases as you move downwards
must be accepted. The content format example of the linked page is shown below:
1B(5,5)(13,12)(8,17)(1,10)(5,5)F
2B(20,20)(30,20)(20,40)(10,40)(20,20)(40,22)(50,32)(30,32)(40,22)F
Figure 1. Graphical representation of the areas given coordinate (x,y) points
Graphical representation of the polygonal shapes whose coordinate points are given in the 1st and 2nd rows above
They are shown together in Figure 1. In the application you will develop, only one line
the graph of the given coordinate points should be drawn. For this reason, the number of lines
The user should be asked to draw the points.
STAGE 2:
The second stage of the project is to determine the amount of reserve value over the surface areas in stage 1.
The drilling and resource extraction part of the resource exploration company constitutes the drilling and resource extraction part of the company.
For this purpose, the shape of the reserve areas drawn in the first stage is determined as the most optimal (most profitable or least loss
situation) must be divided into uniform quadratic pieces of certain dimensions. This
The following constraints should be taken into account during the division process:
Constraint 1: The reserve zone shall be divided into all areas through which the boundary lines pass and all areas within the boundary.
drilling activities will be carried out in the areas. Therefore, the divided quadratic
the sum of the areas is desired to be as minimum as possible. (For a reserve area
the total cost of drilling, the total cost of drilling for all subdivisions that cross over and within the boundary of that zone
will be obtained by multiplying the sum of the quadratic areas by the unit drilling cost. Unit drilling
cost is a variable parameter that can be set by the user between 1 and 10
must be).
Constraint 2: A platform for the storage of extracted resources in each divided quadratic area
must be installed. Only one must be installed in each quadratic area.
the costs of the platforms are identical (Unit platform cost by user
should be a variable parameter that can be determined). In terms of total cost minimisation
The total number of platforms to be installed is also desired to be as minimum as possible.
Constraint 3: The dimensions of the partitioned quadratic areas are 1x1, 2x2, 4x4, 8x8 or at most 16x16.
will be one of the fields. In addition, the boundary neighbours of each quadrilateral are either a
(i.e. the neighbours of a 4x4 quadrilateral must be the larger or smaller of the neighbours of the 4x4 quadrilateral.
The dimensions can be 2x2 or 8x8; it cannot be bounded by a quadratic area of 16x16 or 1x1.
Corner points alone should not be considered as boundaries between areas). A quadratic
can only fully encompass a single reserve zone in the area at the same time, more than one reserve zone
cannot cover the entire territory.

Figure 2 shows example cases of reserve areas divided into quadratic areas according to different dimensions
shown. In case a, the storage platform in the whole region allocated to only 2 quadratic areas
cost is kept to a minimum, while the total grey areas are the highest compared to the other cases.
the total drilling cost is maximised due to the fact that the total drilling cost is maximised. Unlike case a
In case b, the total area is the minimum and the number of frames is the maximum for the total drilling
minimises the cost and maximises the total platform cost. Case d
When the total drilling cost is analysed, it is seen that while the total drilling cost is minimum
the total number of quadrature areas is reduced due to the use of as much as possible
By reducing the number of platforms to be installed, the platform cost is reduced to the optimum level.
REQUIRES
On the page accessed from the web link when the application is first run
coordinate points will be plotted, unit drilling cost and unit platform
cost should be requested from the user. (Drawing only for points on a single line
operation must be performed)
Two separate drawings should be made in the programme.
In the first drawing, the reserve zone formed by the points in the line requested from the user
It should be drawn and visually shown to the user.
The reserve value amount of the plotted areas should be calculated and shown to the user.
(Reserve value = surface area of reserve zones x 10) (More than one reserve zone
the total reserve value must be shown to the user)
For the case with minimum total cost in accordance with the constraints in the second drawing
partitioning should be done and the reserve area divided into quadratic areas should be drawn
should be visually shown to the user. Quadrangular areas of different sizes
should be shown by colouring in colours.
As a result of the second drawing, the user is provided with the total number of platforms and the total number of boreholes,
total platform cost, total drilling cost, total cost (=total drilling
cost + total platform cost) and the amount of profit (= reserve value-total cost)
must be shown to the user.


Sample Project Work:

![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/86bad714-9b45-4d66-b362-0cba7e4b5c0c)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/975311ac-b85f-4db4-9b3a-7ca75270b317)

![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/3a3292ba-7160-4c29-8991-07e97c1fa78f)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/0738f9bd-deb2-46c0-a4f6-4f920f754ff2)

![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/99bfd2ae-4e72-49e7-b553-297ef9c1cdae)
![image](https://github.com/yunushanifi84/Resource-Area-Optimization-Project/assets/69470694/8c613194-f9ba-4350-b266-10a5f738a0fe)

