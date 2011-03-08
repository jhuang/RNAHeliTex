/*
2. slide
I've divided my presentation into 4 parts
- in the first part, I will give an overview of secondary structure component and classical algorithms
- introduce the concept of abstract shapes
- give some ideas about development of a new structure abstraction based on abstract shapes.
In this part, I will point out some problem we might probably encounter
- in the last part, I will give an outlook of the project
If you have some questions during my presentation, feel free to interrupt me.

3. Slide
- In this slide, I will talk about the structural components of RNA.
- RNA is a linear macro-molecule composed of 4 different monomers, namely A, C, G, U.
- except for the most common base pairings :AU and GC, but GU pairs also occur frequently.
- Depending on the enclosing number of base pairs, RNA has different secondary structural components, as the figure showed,
The figure is showing an RNA secondary structure graph. Unpaired positions are marked by ticks.
- Typically, secondary RNA structure contains single-stranded regions, hairpin loop, bulge loop, internal loop, multiloops,
stacking regions and dangling end. Among these RNA secondary structure elements, all double stranded regions are also called
as helical regions, for example this part and this part. The concept is very important, because we will develop a new methods
that based on the helices regions. I will explain it later in this presentation for more details.

4. Slide
- In this slide, I will introduce the classic algorithms for RNA secondary structure prediction.
Namely RNA folding by free energy minimization. The algorithm was first described by Zuker and Stiegler in 1981.
- In this algorithm, we have to assume several conditions, the first condition is RNA folds into only one minimum free-energy structure.
- the second condition is there are no knots.
why we can get away [exclude] the knots during the secondary structure calculation, 2 Reasons are for it.
The first one is it simplifies our problem, the second reason is that secondary structures are used to infer three-dimensional[tertiary] structures,
and knots can be inferred at that stage as well.
- the third condition is that the energy of a particular base pair in a double stranded regions is sequence independent

- Several base pairs form a helical region similar to double stranded DNA. Such stacking of base pairs has a stabilizing effect on the molecule's structure.
However, helix formation always leads to an otherwise free moving, unpaired loop region which destabilizes the molecules' structure
- The runtime of the algorithms is O(N3) (N is the number of nucleotides in the sequence),


5. Slide
1. To better understand it, I prepared a small example,
2. This is an example for calculation of an secondary structure energy, we noticed, the hairpin energy is positive, because it destabilized the structure,
in contrast, the bulge and internal loop have the minus value, because they stabilize the structure.
[TODO: more detailed description]

6. Slide [curve]
- this slide is showing a simple energy landscape about a secondary structure space, the x-axis means different conformations,
the y-axis means the corresponding energy, if the RNA don't have conformational switch, normally the energy difference between minimum free
energy and the first sub-optimal confirmation enough big. or the barriers between them is enough high.

7. Slide
1. Up to this point, all are perfect. some problem are still there, that is, in the minimum free energy model the true structure
is not always the one with the lowest predicted free energy [why], the classical example is for some tRNAs the computed mfe-structure
is not the expected “cloverleaf” but a single long hairpin. but the energy of the native structure should not be too far away
from the predicted minimum free energy, so if we define a range and compute all suboptimal structures within the range, it is possible
to find the native structure,

8. Slide
this is a more extensive energy landscape as what I showed early.
The landscpae descriped the idea that is implemented in the tool RNAsubopt from the Vienna RNA package. It is designed to computer all secondary structures
whose free energy is close to the global minimum free energy within a given energy range. The method is guaranteed to not to miss any structure
whose energy is close to the global minimum free energy.
3. The advantage of the approach is that it gives access to the complete folding space of an RNA sequence. but at the same time we've got another problem,
because the number of suboptimal structures grows exponentially with the size of the energy range. It is not easy to find the native structure
among the huge number suboptimal structure.
The second point is if no additonal clues are given, we don't know which suboptimal structure are better than the other one.


9. Slide
One of the solution is we can further classify secondary structures within the lower energy range with different definition. If we take only few representative for every class so that we can reduce the number of similar structures and the output records will be largely reduced.
The abstract shapes is one approach in this direction.
Abstract shapes is developed by Giegerich and our Bjoern.
//It is inspired by the dot-bracket representation know from the Vienna RNA package
Central to this approach is we do not care about all details of the structures and  abstract from lengths of structural elements or from some elements in total, for example bulge and internal loops.
That means, we classify the structures according to the intuitive shape, because the user is usually only interested in structures that show fundamental differences. Small changes, such as additional base pairs or changing bulge loops are of minor significance. [???], the diagram showing us how the class in abstract shape model in type 5 classified.
Each shape class has a representative structure called shrep. It is the minimum folding energy within the class.



10. Slide
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

11. Slide
1. drawback of abstract shape analysis is the position independence of the abstraction.
2. What is consequence?
3. Firstly, the shape class holds structures which are not as similar as the abstraction suggests.
For example as the figure showed, the RNA in the figure yields the same abstract shape '[]' (square brackets) but actually helices in both sequence lies in different regions.
4. The second drawback, with the abstract shape, it is impossible to set up relationships between different shapes of the same RNA, because the mapping might be ambiguous.
For example in the figure, abstract shape above is one square brackets, abstract shape below is 2 square brackets, Although the second abstract shape looks like doubled as the first one,
but we can't set up correct relations based on the shape information, because the both secondary structures composed of totally different helices.
5. The 2 drawbacks make the current implementation of shape abstraction unsuitable for the analysis of folding landscapes in a detailed fashion.


12. Slide
For the reason we will develop a new structure abstraction that includes the information of positions of helices. To develop it, 2 things have to been considered,
the first is which element we should record for the representation,
the second point is which position we should record for the algorithm.
For the first point, we have candidate helical region of hairpin loop, or helical region of bulge or internal loops and the helical region of multiloop.
As the abstract shape, we can define different abstract
the figure 3 shows us an example, in the example,









up to this point,

question:
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



Today I will talk about my PhD thesis.
The topic of my PhD thesis is …















// but it is still in the exponential area, because the number of shapes grows exponential [diagram]
 */
