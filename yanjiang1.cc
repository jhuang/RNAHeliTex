/*
1. 
Today I will talk about my project.
The topic of my project is about development of a new structure abstraction, we call it as "helices indices of RNAs"
If you have some questions during my presentation, feel free to interrupt me.

2. 
I've divided my presentation into 4 parts
- in the first part, I will talk about the basic secondary structure elements of RNA and introduce a classical RNA secondary structure prediction algorithm
- because the concept of "helices indices of RNAs" is based on the concept of "abstract shapes", that was developed by Bjoern, so I will introduce 
the concept of "abstract shapes" in the 2nd part.
- give the basic idea about the helices indices. 
- in the last part, I will give an outlook of the project

3. 
- In this slide, I will talk about the basic secondary structural elements of RNA,
- As the figure showed, RNA is composed of different secondary structural elements,  like 6 种.
- Among them, dangling end and base stacking are energy favorable elements, 
- at the same time, such energy favorable elements lead to formation of energy unfavorable elments like 4 种.
- all double stranded regions are also called as as 'helical regions', for example this part and this part. The concept is very important, because we will develop a new methods
that based on the helices regions. I will explain it later in this presentation for more details.

4. 
- In this slide, I will introduce the classic algorithms for RNA secondary structure prediction.
  namely Zuker algorithm. The algorithm was first described by Zuker and Stiegler in 1981.
- In this algorithm, we have to assume one condition, namely we get away the knots from the calculation.
  The reason why we can get away the knots from the calculation is the calculation result of secondary structure prediction are used to infer
  3-dimensional structures and knots can be inferred at this stage as well.
- the basic idea is sequence can be folded into many different secondary structures.
                    furthermore, we can calculate for every secondary structure a clear energy value according to the free enery model.
                    after that, the algorithm choose the structure with the minimum free energy.
- The runtime of the algorithms is O(n3) where n is the length of sequence,
- From this argorithm, we can get only one solution.

5. 
- To better understand it, I prepared a small example,
- as the figure shows, the secondary structure consists of a hairpin loop, dangling end, 2 base stacking, a bulge loop,
- as I said earlier, the hairpin loop and  dangling end are energy favorable, the have the negative free energy, and hairpin loop and
  bulge loop are energy unfavorable, they have positive free energy.
- after addition of all elements, we get the energy value -4.6 kcal/mol.
  In Zuker algorithm, we calculate the free energy for every secondary structure, and after comparing it computes the minimum.

6. [curve]
- if we draw all the energy value of secondary structure corresponding to the conformations, we get a landscape. 
- as the figure showed, the x-axis means conformations, the y-axis means free energy, if the RNA don't have conformational switch, normally the energy difference between minimum free
energy and energy of the first sub-optimal confirmation is enough big.

7. 
- As I just said, The Zuker algorithm can only find the mfe structure, 
  aber in practice, the native structure is not always the one with the lowest predicted free energy, but the energy of the native structure should not be too far away
  from the predicted minimum free energy, and it is normally a local minimum.
- what can we do? one of solutions is we we define a range and enumerate all suboptimal 照 读。 it is possible to find the native structure,

8. 
- the figure shows us the solution of last slide, we set a linie in the energy landscape and calculate all suboptimal structure under the linie.
- but it caused another problem, namely the number of suboptimal structures grows exponentially with the size of the energy range,
  further more, the runtime grows also expnentially.
- The second point is if no additonal clues are given, we don't know which suboptimal structure are better than the other one.
- How can we do?

9. 
- One of the solution is we can further classify secondary structures within the lower energy range with different definition.
  If we take only few or only one representative for every class so that we can reduce the number of similar structures 
  and the output records will be largely reduced.
- The abstract shapes is one approach in this direction.
- Abstract shapes is developed by Giegerich and our Bjoern.
- intial idea: 
  - the user is usually only interested in structures that show fundamental differences. 
  - Small changes, such as additional base pairs or changing bulge loops are of minor significance. 
- Central to this approach is we do not care about all details of the structures and abstract from lengths of structural elements or from some elements in total, 
  for example in abstract shape type 5, all loops excepts for internal loop and multiloop are abstracted.
- each shape has a representative structure called shrep. It is structrue with the minimum free energy within the shape class.    


10. 
- this figure shows an example output from software RNAshapes in an energy range of 5 kcal/mol above the mfe.  
- the abstract shape type is 5
- the picuture above is the corresponding 2D representation of the 3 records below.
- So lets look in a bit more detail at the below part. 
- on the left side, it is abstract shape in type 5, as I said before, shape type 5 only take helical regions of hairpin loop and multiloop into accout,
  so for example, for the first record, we only consider the hairpin loop in the middle of the secondary structure. the helical regions of the 2 loops are represented as a pair of 
  opening and closing square brackets.
- in the middle part below is the classical dot-bracket representation for secondary structure, in this representation, two matching parentheses represent
  a base pairs between the corresponding positions and a dot stands for an unpaired base.   
- on the right side, is the mfe with the abstract shape class, namely the energy of the secondary structure in the middle part.
- In the example, we notice, that it exists 3 abstract shape classes whose energy spans from -6.3 to -1.3 kcal/mol if we set a range energy as 5 kcal/mol.


11. 
- the abstract shape works pretty well, but one drawback is still there. namely 照读. 
- that means, we can not track the positions of RNA secondary structure elements 
- What is consequence?
- the consequence is that with the model, it is impossible to set up relationships between different shapes, because the mapping might be ambiguous.
- For example in the figure, abstract shape above is one square brackets, abstract shape below is 2 square brackets, Although the second abstract shape 
  looks like doubled as the first one, but we can't set up correct relations based on the shape information, because the both secondary structures 
  composed of totally different helices.
- the drawback make the current implementation of shape abstraction unsuitable for the analysis of folding landscapes in a detailed fashion.


12. 
- for the reason we will develop a new structure abstraction that includes the information of positions of helices, namely helices indices.
- to develop it, 2 things have to been considered,
- the first thing is which element we should take to record the positions.
- the second point is which position of elements we should take. 
- for the first point, we have 4 candidate: hairpin loop, multiloop, bulge or internal loops and any combinations of them.
  if we choose a very less abstracted of secondary component, for example if we only track the hairpin position,
  the advantage is the output records is relatively less and the program will run faster.
  The disadvantage is such simplification will loses the accuracy because it ignores some detailed information.
- for the second point, we have also 4 candidates to track to the positions.  
  i means the beginning postion of the helices,
  j means the end position of helices,
  the combination i,j means we record both beginning position and end positon of the helices 
  i+j/2 means we record the central position of base pair.
  we consider the central positions models have some advantages over the other, because in this model we need
  only storage one number for every loop but it incorporate the information of both positions

13. 
- To better understand it, I prepared a small example,
- In this example, we abstract from multiloop, bulge loop and internal loop. We only consider hairpin loop and use the central positions.
- In addition, we take the central position to record these loops.
- So as the figure showed, the structure is composed of 2 hairpin loops which are closed at the position (i,j) and (k,l).
  The position of i is 8, j is 13, k is 35 and l is 41, so the central position of the first hairpin loop is 10.5 and the second one is
  38, Thus, this structure would be abstracted to [10.5, 38].

14. 
- In this slide, I will show the first test result on a test RNA sequence. 
- In this example, we take the multiloop and hairpin loop into account and use the central position.
- the most interesting point from the result is, the 2 conformations with helix index 27 and 38, appear as the first 2 results.
  and if we search further in the list, we can find a combination of the 2 central position at the bottom of the list, namely the records here.
- What does it mean? the solution is in the next slide.


15. 
- It is easy to understand, the first record is the global minimum structure and the second record is a lowest suboptimal structure.
- They have almost the same free energy.
- From the list last slide, a structure that combined the 2 helices exists, we can treat the structure as the saddle point.
  If we will move from mfe structure to the lowest suboptimal structure, we have to pass the saddle point.
  Because the free energy of all the recognized structure are clear, thus, through this simple analysis we can calculate the energy
  barriers between the alternate structure and saddle structure. it is 8.4 kcal/mol.

16. 
- from this slide, I will point out one serious problem we might encounter.
  namely although both the abstract shapes and helices indices space grow exponentially with sequence length and suboptimal energy range, 
  the helices indices space grows considerably faster. 
- The figure shows the comparison of helices indices space with abstract shapes space
  The linie is regression linie of the helices indices space,
  The linie is regression linie of the abstract shapes space,
- We're noticing that the y-axis is exponentially defined, so it means, the steepness of the linie is the exponent of the sequence length. 
  the number of all 2 type structures grow exponential with the sequence length
  but the degree of steepness are different, the steeper the curve, the worse the runtime will be,
- In practice, with a sequence length of 70 nt, the unmber of suboptimal helices structures already exceeds 1 million records.
  and the program needs about 1 hour to calculate for 70 nt and about 30 hours to calculate for 72 nt sequence under our 32 cores super computer.
- how can we solve this problem?

17. 
- one idea is that we can set an energy range to limit the helices indices space.
- the figure shows the evaluation result by setting different energy ranges.
- in the first linie, we let the energy unlimited, the exponent is the same as last slide, it is about 0.18 [how does one read it?]
- if we set an energy range 20 kcal/mol, so the exponent of the space will be reduced to one third, it amounts to 0.12,
- on the last curve, we're noticing, the exponent value is only 0.036. that means, the runtime grows almost as polynomial curve.

18. 
- in last slide, I will give an outlook of the project.
- at first, we will develop a new structure abstraction, namely the helices indices that I just explained.
- after that, the idea will be implemented with the ADP framework in C++ programming language,
- as next, the implemented software will be evaluated by comparing with another program.
- because different RNA have different energy landscape, 
  we can classify the RNA using the information of energy barriers information that are obtained from the software developed within this project, 
  in the last part, we will design a RNA class predictors.

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



11.03.2011
The idea is from Bjoern.
In this part, I will also point out one serious problem we might encounter


The figure shows an RNA secondary structure graph. Unpaired positions are marked by ticks.
- Typically, secondary RNA structure contains single-stranded regions, hairpin loop, bulge loop, internal loop, multiloops,
stacking regions and dangling end. Among these RNA secondary structure elements, all double stranded regions are also called

 RNA folding by free energy minimization.
 
 
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

   in the example, the secondary stucture consists of a hairpin loop, here is it, here is a base stacking element, here is a bulge loop,
   here is again a base stacking, at the bottom there is a dangling end. As I said last slide, only the base stacking stabilize the
   structure, therefore they have minus value and in contrast, all loops destabilize the structure, therefore they have positive value
   
  adding all the separate elements, we get an energy value for the structure. that also means, every secondary structure has its
  only own value.
  
  A sequence can fold in many different secondary structure, 
  
  that are derived from the same sequence in a graph, 
  we can get a landscape.
  
   or the barriers between them is enough high.
   
   the classical example is for some tRNAs the computed mfe-structure
is not the expected “cloverleaf” but a single long hairpin. 

- so if we define a range and compute all suboptimal structures within the range, 

So some researcher developed further tool to overcome the problem, for example, the tool RNAsubopt from the Vienna RNA package. It is designed to computer all secondary structures
whose free energy is close to the global minimum free energy within a given energy range. The method is guaranteed to not to miss any structure
whose energy is close to the global minimum free energy.
3. The advantage of the approach is that it gives access to the complete folding space of an RNA sequence. but at the same time we've got another problem,
because the number of suboptimal structures grows exponentially with the size of the energy range. It is not easy to find the native structure
among the huge number suboptimal structure.

//It is inspired by the dot-bracket representation know from the Vienna RNA package


[???], the diagram showing us how the class in abstract shape model in type 5 classified.

That means, we classify the structures according to the intuitive shape, because 

the diagram showing us how the class in abstract shape model in type 5 classified.


in this energy range


  in the first records, on the left side is the shape representative for the shape class, the the energy of the shrep is -6.3, on the right side
  and it consists of 2 hairpin loops, one multiloop and bulge loop, but only the hairpin loops and multiloop are represented by the abstract shape.
  in contrast, In the 2nd record, all 2 hairpin loop are represented by the shape
  in the last record, the hairpin is described, but the internal loop is abstracted.
  
  
  independence of the abstraction.
  
  - Firstly, the shape class holds structures which are not as similar as the abstraction suggests.
For example as the figure showed, the RNA in the figure yields the same abstract shape '[]' (square brackets) but actually helices in both sequence lies in different regions.
4. The second drawback,

The nex point is to

record for the algorithm.

decide which positions of the base pair to use, we have 4 candiates.
Among the 4 candiates

Theoretically, one can combine the first part with the second part arbitrarily. but some consequence for different combinition,

, it is a balance of the storage and
information.

The abstraction doesn't take bulge, internal and multiloop into account, but especially multiloop, they are structurally important.
For the reason, we will implement program with some different options, different helical regions from different loops will be considered
in these options.
For example, the most abstract level is helix type 5, it remains only the helical regions of hairpin loop.
                 less abstract level is helix type 4, it will include the multiloop except for hairpin loop and so on.
                 
of the proposed abstraction function on the complete set of suboptimal structures for a test
RNA. It was computed by first trival version of the program helices shape.        

[What can we get more information from the list?]

- At first, I will explain what is the structure space, helices space and shapes space.
  The structure space means the set of all the suboptimal structures.
  The helices space means the set of all suboptimal abstract helices structures.
  The shapes space means the set of all suboptimal abstract shapes structures.
  
    The figure shows an increasing nr. of different type structures with increasing sequence length.
  In more details,
  
    The linie is regression linie of the  structure space,
    among the 2 type space, there is a common point, namely the number of all 3 type structures grow
  exponential with the sequence length, because
  
  Compring with structure space, the curve of helices structure is less steep, but it is still about 0.18 big.
  
  because different RNA classes have characteristic features within their folding space, for example, the riboswitches have
2 equally low, but well separated minima, while miRNA precursors has only one deep minimum,

the the different energy landscape types of different RNA classes and 
the the different energy landscape types of different RNA classes and 
 */
