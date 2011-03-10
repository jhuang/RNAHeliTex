/*
1. 
Today I will talk about my project.
The topic of my project is about development of a new structure abstraction, we call it as "helices indices of RNAs"
If you have some questions during my presentation, feel free to interrupt me.

2. 
I've divided my presentation into 4 parts
- in the first part, I will give an overview of RNA secondary structure elements and introduce a classical RNA secondary structure prediction algorithm
- because the concept of "helices indices of RNAs" is based on the concept of "abstract shapes", so I will introduce 
the concept of "abstract shapes" in the 2nd part.
- give the basic idea about the helices indices. The idea is from Bjoern.
In this part, I will also point out one serious problem we might encounter
- in the last part, I will give an outlook of the project

3. 
- In this slide, I will talk about the basic secondary structural elements of RNA.
- As the figure showed, RNA is composed of different secondary structural elements, 
The figure shows an RNA secondary structure graph. Unpaired positions are marked by ticks.
- Typically, secondary RNA structure contains single-stranded regions, hairpin loop, bulge loop, internal loop, multiloops,
stacking regions and dangling end. Among these RNA secondary structure elements, all double stranded regions are also called
as helical regions, for example this part and this part. The concept is very important, because we will develop a new methods
that based on the helices regions. I will explain it later in this presentation for more details.

4. 
- In this slide, I will introduce the classic algorithms for RNA secondary structure prediction.
  namely RNA folding by free energy minimization. The algorithm was first described by Zuker and Stiegler in 1981.
- In this algorithm, we have to assume one condition, namely we get away the knots from the calculation.
  why we can get away [exclude] the knots from the secondary structure calculation, 2 Reasons are for it.
  - The first one is it simplifies our problem, 
  - the second reason is that secondary structures are used to infer three-dimensional[tertiary] structures,
  and knots can be inferred at that stage as well.

- A given RNA sequence can be folded due to many possible combinations of base pairings into exponentially 
  many different secondary structures.
- every secondary structure can be attached with an energy value according to some rules. 
- Among the basic secondary structural elements,
  only the base stacking regions and dangling end stabilize the structure, the other elements for example hairpin loop, bulge loop,
  internal loop and multiloops destalibize the structure.
- the algorithm computes with a given RNA sequence the structure with the minimum free energy
- The runtime of the algorithms is O(N3) (N is the number of nucleotides in the sequence),
- From this argorithm, we can get only one structure

5. 
- To better understand it, I prepared a small example,
   in the example, the secondary stucture consists of a hairpin loop, here is it, here is a base stacking element, here is a bulge loop,
   here is again a base stacking, at the bottom there is a dangling end. As I said last slide, only the base stacking stabilize the
   structure, therefore they have minus value and in contrast, all loops destabilize the structure, therefore they have positive value
- after adding all the separate elements, we get an energy value for the structure. that also means, every secondary structure has its
  only own value.
  A sequence can fold in many different secondary structure, if we draw all the energy value of many different secondary structure that are derived from the same sequence in a graph, 
  we can get a landscape.

6. [curve]
- this slide is showing a simple energy landscape about a secondary structure space, the x-axis means different conformations,
the y-axis means the corresponding energy, if the RNA don't have conformational switch, normally the energy difference between minimum free
energy and the first sub-optimal confirmation enough big. or the barriers between them is enough high.

7. 
1. As I just said, The Zuker algorithm can only find the mfe structure, aber in practice, 
the native structure is not always the one with the lowest predicted free energy [why], the classical example is for some tRNAs the computed mfe-structure
is not the expected “cloverleaf” but a single long hairpin. but the energy of the native structure should not be too far away
from the predicted minimum free energy, so if we define a range and compute all suboptimal structures within the range, it is possible
to find the native structure,

8. 
So some researcher developed further tool to overcome the problem, for example, the tool RNAsubopt from the Vienna RNA package. It is designed to computer all secondary structures
whose free energy is close to the global minimum free energy within a given energy range. The method is guaranteed to not to miss any structure
whose energy is close to the global minimum free energy.
3. The advantage of the approach is that it gives access to the complete folding space of an RNA sequence. but at the same time we've got another problem,
because the number of suboptimal structures grows exponentially with the size of the energy range. It is not easy to find the native structure
among the huge number suboptimal structure.
The second point is if no additonal clues are given, we don't know which suboptimal structure are better than the other one.


9. 
One of the solution is we can further classify secondary structures within the lower energy range with different definition. If we take only few representative for every class so that we can reduce the number of similar structures and the output records will be largely reduced.
The abstract shapes is one approach in this direction.
Abstract shapes is developed by Giegerich and our Bjoern.
//It is inspired by the dot-bracket representation know from the Vienna RNA package
Central to this approach is we do not care about all details of the structures and  abstract from lengths of structural elements or from some elements in total, for example bulge and internal loops.
That means, we classify the structures according to the intuitive shape, because the user is usually only interested in structures that show fundamental differences. Small changes, such as additional base pairs or changing bulge loops are of minor significance. [???], the diagram showing us how the class in abstract shape model in type 5 classified.
Each shape class has a representative structure called shrep. It is the minimum folding energy within the class.



10. 
this slide shows predicted shreps in an energy range of 5 kcal/mol above the mfe.
the left side is the classical dot-bracket representation, in the representation, two matching parentheses represent
a base pairs between the corresponding positions. and a dot stands for an unpaired base. On the right side, is the abstract
shape 5. Abstract shape 5 most abstract type. It abstracts from internal loop, bulge loop and stack lengths.
Only the helix nesting pattern of hairpin loop and multiloop are remaining, the helical regions of the 2 loops are represented as
a pair of opening and closing square brackets.
- In the example, we find 3 abstract shapes in this energy range from -6.3 to -1.3 kcal/mol.
  in the first records, on the left side is the shape representative for the shape class on the right side, the energy of the shrep is -6.3,
  and it consists of 2 hairpin loops, one multiloop and bulge loop, but only the hairpin loops and multiloop are represented by the abstract shape.
  in contrast, In the 2nd record, all 2 hairpin loop are represented by the shape
  in the last record, the hairpin is described, butthe internal loop is abstracted.

11. 
1. drawback of abstract shape analysis is the position independence of the abstraction.
2. What is consequence?
3. Firstly, the shape class holds structures which are not as similar as the abstraction suggests.
For example as the figure showed, the RNA in the figure yields the same abstract shape '[]' (square brackets) but actually helices in both sequence lies in different regions.
4. The second drawback, with the abstract shape, it is impossible to set up relationships between different shapes of the same RNA, because the mapping might be ambiguous.
For example in the figure, abstract shape above is one square brackets, abstract shape below is 2 square brackets, Although the second abstract shape looks like doubled as the first one,
but we can't set up correct relations based on the shape information, because the both secondary structures composed of totally different helices.
5. The 2 drawbacks make the current implementation of shape abstraction unsuitable for the analysis of folding landscapes in a detailed fashion.


12. 
For the reason we will develop a new structure abstraction that includes the information of positions of helices. To develop it, 2 things have to been considered,
the first is which element we should record for the representation,
the second point is which position we should record for the algorithm.
For the first point, we have candidate helical regions of hairpin loop, the helical regions of multiloop and helical regions of bulge or internal loops.
The nex point is to decide which positions of the base pair to use, we have 4 candiates. Among the 4 candiates
i means the beginning postion of the helices,
j measn the end position of helices,
or we record the the beginning position of the helices and end position together as a data structure
the last possibility is we take only the central position of the base pair.
Theoretically, one can combine the first part with the second part arbitrarily. but some consequence for different combinition,
if we choose a very less abstracted of secondary component, for example if we only track the hairpin position,
the advantage is the output records is relatively less and the program will run faster.
The disadvantage is such simplification will loses the accuracy because it ignores some detailed information.
For the second point, we consider the central positions models have some advantages over the other, because in this model we need
only storage one number for every loop but it incorporate the information of both positions, it is a balance of the storage and
information.

13. 
To better understand it, I prepared a small example,
In this example, we abstract from multiloop, bulge loop and internal loop. We only consider hairpin loop to track the positions,
In addition, as I explained last slide, we take the central position to record these loops.
So as the figure showed, the structure is composed of 2 hairpin loops which are closed at the position (i,j) and (k,l) respectively.
The position of i is 8, j is 13, k is 35 and l is 41, so the central position of the first hairpin loop is 10.5 and the second one is
38, Thus, this structure would be abstracted to [10.5, 38].
The abstraction doesn't take bulge, internal and multiloop into account, but especially multiloop, they are structurally important.
For the reason, we will implement program with some different options, different helical regions from different loops will be considered
in these options.
For example, the most abstract level is helix type 5, it remains only the helical regions of hairpin loop.
                 less abstract level is helix type 4, it will include the multiloop except for hairpin loop and so on.


14. 
In this slide, I will show the first test of the proposed abstraction function on the complete set of suboptimal structures for a test
RNA. It was computed by first trival version of the program helices shape.
In this example, we take the multiloop and hairpin loop into account, the representation position is the central position.
The most interesting point from the result is, the 2 conformations with helix index 27 and 38, appear as the 2 first results.
And if we search further in the list, we can find a combination of the 2 central position at the bottom of the list, namely
the records.
What does it mean? [What can we get more information from the list?]
The solution is in the next slide.


15. 
It is easy to understand, the first record is the global minimum structure and the second record is a lowest suboptimal structure.
They have almost the same free energy.
From the list last slide, a structure that combined the 2 helices exists, we can treat the structure as the saddle point.
If we will move from mfe structure to the lowest suboptimal structure, we have to pass the saddle point.
Because the free energy of all the recognized structure are clear, thus, through this simple analysis we can calculate the energy
barriers between the alternate structure and saddle structure. it is 8.4 kcal/mol.


16. 
- At first, I will explain what is the structure space, helices space and shapes space.
  The structure space means the set of all the suboptimal structures.
  The helices space means the set of all suboptimal abstract helices structures.
  The shapes space means the set of all suboptimal abstract shapes structures.
- The figure is showing the comparison of helices space with structure space and shapes space.
  The figure shows an increasing nr. of different type structures with increasing sequence length.
  In more details,
  The linie is regression linie of the  structure space,
  The linie is regression linie of the  helices structure space,
  The linie is regression linie of the  abstract shape space,
- We're noticing that among the 3 type space, there is a common point, namely the number of all 3 type structures grow
  exponential with the sequence length, because the y-axis is exponentially defined.
  But the degree of steepness are different, the steeper the curve, the worse the runtime will be,
- because the steepness of the linie means the exponent of the sequence length.
  Compring with structure space, the curve of helices structure is less steep, but it is still about 0.18 big.
  In practice, with a sequence length of 70 nt, the unmber of suboptimal helices structures already exceeds 1 million records.
  and the program needs about 1 hour to calculate for 70 nt and about 30 hours to calculate for 72 nt sequence under our 32 cores super computer.
- how can we solve this problem?

17. 
- one idea is that we can set an energy range to limit the helices space.
- the figure shows the evaluation result by setting different energy range.
  in the first linie, we let the energy unlimited, the exponent is the same as last slide
  if we set an energy range 20 kcal/mol, so the exponent of the space will be reduced to one third, it amounts to 0.12,
  on the last curve, we noticed, the exponent value is only 0.036. that means, the runtime grows almost as polynomial curve.

18. 
in last slide, I will give the schedule of the project.
At first, we will develop the new abstraction idea, namely the helices index that I just explained.
after that, The idea will be implemented in C++ programming language,
As next, the implemented software will be evaluated by comparing with another program.

Because different RNA classes have characteristic features within their folding space, for example, the riboswitches have
2 equally low, but well separated minima, while miRNA precursors has only one deep minimum, based on the energy landscape
difference and the algorithms developed within this project, in the last part, we will
design a RNA class predictors.


19. 
Thank you for your attention!
Are there any questions?





questions:
1. How was implemented the idea in detail?
dynamic programming is a method for solving complex problems by breaking them down into simpler subproblems.
The key idea behind dynamic programming is quite simple. In general, to solve a given problem, we need to
solve different parts of the problem (subproblems), then combine the solutions of the subproblems to reach an overall solution.
Often, many of these subproblems are really the same. The dynamic programming approach seeks to solve each subproblem only once,
thus reducing the number of computations. This is especially useful when the number of repeating subproblems is exponentially large.
(Page 40 from Diss)

2. Why is mfe structures not the native one?
This can be explained by the existence of modified bases in native tRNAs, which leads to the formation of a structure that is not
the optimal under the energy model used.

3.
It exists a software, it can analyse the folding space completely. Only the runtime of the program is very bad.
This is also the reason why we will develop a new program because we will improve the runtime.
























3. Slide
- a better reason for excluding knots is that secondary structures are used
and knots occurs not very often in RNA molecules so in most case the calculation results satisfied the accuracy requirement,
that for known true RNA structures
consider only the problem without pseudoknots,
you can usually find a set of at least 95% of the base pairs that does not contain any pseudoknots, that means, if we get away the pseudoknots,
the calculation results satisfied in most cases the accuracy requirement,


5. Slide
- A nearest neighbor model is used to predict the Gibbs free energy change of RNA secondary structure formation.
- The free energy of each motif depends on only the sequence of that motif and the most adjacent base pairs.
- The total free energy is the sum of the increments.
Secondary structure of small RNA molecules is largely determined by strong, local interactions such as hydrogen bonds and base stacking. Summing the free energy for such interactions should provide an approximation for the stability of a given structure. To predict the folding free energy of a given secondary structure, an empirical nearest-neighbor model is used. In the nearest neighbor model the free energy change for each motif depends on the sequence of the motif and of its closest base-pairs.[1]  The model and parameters of minimal energy for Watson–Crick pairs, GU pairs and loop regions were derived from empirical calorimetric experiments, the most up-to-date parameters were published in 2004,[2]  although most software packages use the previous set assembled in 1999.[3]
The simplest way to find the lowest free energy structure would be to generate all possible structures and calculate the free energy for it, but the number of possible structures for a sequence increases exponentially with the length of RNA (Number of secondary structures = (1,8)N , N- number of nucleotides).[4] For longer RNA molecules, the number of possible secondary structures is huge: a sequence of 100 nucleotides has more than 1025 possible secondary structures.[1]


that is feasible with respect to the nearest neighbour energy model.

it has only one global maximal and

With the algorithm we can find native structure easily.






The problem can be solved by
- filtering the output to reduce the number of similar structures
- directly reducing the number of solutions with some restriction (for example, hairpin has at least 4 bases)
- however, such step might occur the danger of missing the native structure



An abstract shape represents a class of similar structures sharing a common pattern of helix nesting and adjacency.
// when we feel that two structures are similar, they should either have the same shape.
 and it only retains haipins and multiloops. But abstracts from stack lengths, bulges, internal loops and single-stranded regions.



















// but it is still in the exponential area, because the number of shapes grows exponential [diagram]
 *
As the abstract shape, we can define different abstract
the figure 3 shows us an example, in the example,

The figure shows the possible path .

The combination of the 2 helices are treated as the

- the third condition is that the energy of a particular base pair in a double stranded regions is sequence independent




like it did in abstract shape,
helices type means different abstraction level.

up to this point,

======================================================================
- RNA is a linear macro-molecule composed of 4 different monomers, namely A, C, G, U.
- except for the most common base pairings :AU and GC, but GU pairs also occur frequently.
Depending on the enclosing number of base pairs,

the first condition is RNA folds into only one minimum free-energy structure.
it  there are no knots.

- One of the first attempts to predict RNA secondary structure was made by
- Several base pairs form a helical region similar to double stranded DNA. 
    \item destabilized by hairpin, internal and bulge loops
    
Such stacking of base pairs has a stabilizing effect on the molecule's structure.    
However, helix formation always leads to an otherwise free moving, unpaired loop region which destabilizes the molecules' structure
calculate the minimum free-energy 

2. This is an example for calculation of an secondary structure energy, we noticed, the hairpin energy is positive, because it destabilized the structure,
in contrast, the bulge and internal loop have the minus value, because they stabilize the structure.
[TODO: more detailed description]

Up to this point, all are perfect.

some problem are still there, that is, in the minimum free energy model

this is a more extensive energy landscape as what I showed early.
The landscpae descriped the idea that is implemented in
 */