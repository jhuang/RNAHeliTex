
1. 
- Today I will talk about my project.
- The topic of my project is about development of a new structure abstraction, we call it as "helices indices of RNAs"
- If you have some questions during my presentation, feel free to interrupt me.

2. 
I've divided my presentation into 4 parts
- in the first part, I will talk about the basic secondary structure elements of RNA and introduce a classical RNA secondary structure prediction algorithm
- because the concept of "helices indices of RNAs" is based on the concept of "abstract shapes", that was developed by Bjoern, so I will introduce 
the concept of "abstract shapes" in the 2nd part.
- give the basic idea about the helices indices. 
- in the last part, I will give an outlook of the project

3. 
- In this slide, I will talk about the basic secondary structural elements of RNA,
- As the figure showed, RNA is composed of 2 kinds of elements, like 6 种.
  the first kind is energy favorable part, it includes dangling end and base stacking
- such energy favorable elements lead to formation of energy unfavorable elments, they are 4 种.
- all double stranded regions are also called as as 'helices', it is always related with a loop type. 
  for example we call this part as helics of hairpin loop, this part as helices of multiloop, this part as helices of bulge loop, this part as helices of internal loop. 
- the concept is very important, because we will develop a new methods
  that based on the helices. I will explain it later in this presentation in more detail.

4. 
- In this slide, I will introduce the classic algorithm for RNA secondary structure prediction.
  namely Zuker algorithm. The algorithm was first described by Zuker and Stiegler in 1981.
- the basic idea is sequence can be folded into many different secondary structures.
                    furthermore, we can calculate for every secondary structure a unambiguous free energy value by adding the free energies of all elements of the secondary structure.
                    after that, the algorithm choose the structure with the minimum free energy.
- (advantage) The runtime of the algorithms is O(n3) where n is the length of sequence,
- (disadvantage) From this argorithm, we can get only one solution.

5. 
- To better understand it, I prepared a small example,
- as I just said, in Zuker algorithm, for every secondary structure we calculate a free energy value by ...
- as the figure shows, the secondary structure consists of a hairpin loop, dangling end, 2 base stacking, a bulge loop,
- among them, the hairpin loop and dangling end are energy favorable, the have the negative free energy, and in contrast, hairpin loop and bulge loop are energy unfavorable, they have positive free energy.
- after addition of all elements, we get a free energy for the whole secondary structure, namely -4.6 kcal/mol.

6.
- if we calculate free energy for every secondary structure and draw it on a graph, we get a landscape.
- as the figure showed, the x-axis means conformations, 
                        the y-axis means free energy, 
  normally, if a RNA molecule don't have conformational switch, the energy difference between minimum free energy and energy of the first sub-optimal confirmation is enough big, so that the mfe-point can not go up and reach the point.
- In Zuker algorithm, we calculate only this point.

7. 
- aber in practice, the native structure is not always the one 照 读...
- what can we do to find the native structure? One of solutions is that we define a range and enumerate all suboptimal 照 读...

8. 
- the figure shows the idea I just explained last slide, firstly, we define a line in the energy landscape and calculate all suboptimal structure under the line.
- but it caused another problem, namely the number of suboptimal structures grows exponentially with the size of the energy range.
- How can we solve the problem?




9. 
- one is the solution is we can further classify secondary structures space
- abstract shapes is one approach in this direction
- the initial idea is the user is only interesting in structures that show fundamental differences
- small change like bulge loop and internal loops are not every important.
- the idea is we can abstract from such unimportant elements, for example, bulge loop and internal loops
- last point is every shape has a representative, it is also called as shrep, it is minimum free energy within shape class.

10. 
- this figure shows an output example from abstract shapes by setting an envergy range of 5 kcal/mol above the mfe.  
- the picture above is 2 dimension representation, the picture below is the text form.
- from the intuitive perspective, the abstract shape is similar than the 2 dimension version. for example in record 3, as seen from the 2 dimension version, it is a cloverleaf, correspondingly, the abstract shape is a pair brackets that nest 3 pairs inner brackets. 

11. 
- the abstract shape works pretty well, but one drawback is still there. namely 照读. 
- What is consequence of the drawback?
- To explain the drawback, I prepared an example, as the figure shows, although the abstract shape above and below are identical, but position of the hairpin loop are totally different. 
- the drawback make 照读...





12. 
- this is the reason why we will develop a new structure abstraction namely helices indices. It includes the information of positions of helices.
- to develop it, 2 things have to been decided,
- the first thing is Which secondary structure element should be recorded?
- we have 4 candidate ...
- the second point is which position of this element should be recorded?
- we have also 4 candidates, 
  i is first position of helix, j is last position of helix, 
  we can also record the both positions at the same time or the central position of them.

13. 
- To better understand it, I prepared a small example,
- In this example,  We record only hairpin loop and use the central position 
- So as the figure showed, the structure is composed of 2 helices, namely this one and this one. 
  because we abstract from the bulge loop, so we don't consider this part.
- the position of i is 8, j is 13, i+j/2 is 10.5, similarly, k is 35 and l is 41, and k+l/2 is 38. Therefore, this structure would be abstracted to [10.5, 38].

14. 
- the slide showed 照读
- in this example, we record multiloop and hairpin loop and use the central position. To differ from multiloop and hairpin loop, we attach a letter 'm' to the helices indices of multiloop. for example, in the record, 30m means the position comes from a multiloop.
- the most interesting information behind the list are 3 records, namely this one, this one and this one
- if we compare the 3 records, we can find the helices indices of this record is a combination of the first 2 records.
- what does it mean? ths answer is in the next slide.

15. 
- if we draw the 3 records in energy landscape, it must be like this.
- the first record is global minimum structure and the second record is a local minimum. They have almost the same free energy.
- furthermoare, the combination records is a saddle point
- so if we move from this point to this point, we have to pass the saddle point. Because the free energy of all 3 helices indices are known, therefore, we can calculate the difference easily. the difference is barrier energy. 
- in our example, （返回去）, the mfe-point has energy 10.7, this point has energy 2.3, and the barrier energy is about 8.4




16. 
- from this slide, I will talk about the first problem we encountered, this is a runtime problem.
- the figure shows 照读
  in the figure, x axis is sequence length, y axis is number of helices indices or abstract shapes
  the line means the helices indices space, the line means the abstract shapes space.
- we notice, 照读, therefore it caused a runtime problem. In practice, for a sequence with 72 nucleotides, we need about 32 hours to calculate the helices indices on our super computer, it is not satisfactory.
- how can we solve this problem?

17. 
- one solution is that 照读,
- the figure shows 照读
- there are altogether 5 lines in the figure
  the first line means the helices indices without energy limitation
      second is with a energy limit of 20 kcal/mol, this is with 15, this is with 10, this is with 5.
- although all helices indices spaces grow exponentially with sequence length, but the degree of steepness are different, 
- the tendency is the lower the energy range (is), the flater the line (is) and the better the runtime will be.
- so if we set a lower enery range on the calculation, we will get a better runtime and solve the problem.

18. 
- in last slide, I will give an outlook of the project.
- at first, we will develop a new structure abstraction, namely the helices indices 
- after that, the idea will be implemented based on the idea.
- of course, the software will be evaluated by benchmark program
- lastly, we will design a RNA class predictor

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


4.
- In this algorithm, we have to assume one condition, namely we get away the knots from the calculation.
  The reason why we can get away the knots from the calculation is the calculation result of secondary structure prediction are used to infer
  3-dimensional structures and knots can be inferred at this stage as well.





















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


- this is step 2 of the Zuker algorithm.
  In Zuker algorithm, we calculate the free energy for every secondary structure, and after comparing it computes the minimum.
  
  
  further more, the runtime grows also expnentially.
- The second point is if no additonal clues are given, we don't know which suboptimal structure are better than the other one.  


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



- What is consequence?
- the consequence is that with the model, it is impossible to set up relationships between different shapes, because the mapping might be ambiguous.
- For example in the figure, abstract shape above is one square brackets, abstract shape below is 2 square brackets, Although the second abstract shape 
  looks like doubled as the first one, but we can't set up correct relations based on the shape information, because the both secondary structures 
  composed of totally different helices.
  
  
  if we choose a very less abstracted of secondary component, for example if we only track the hairpin position,
  the advantage is the output records is relatively less and the program will run faster.
  The disadvantage is such simplification will loses the accuracy because it ignores some detailed information.  
  
  
    the combination i,j means we record both beginning position and end positon of the helices 
  i+j/2 means we record the central position of base pair.
  we consider the central positions models have some advantages over the other, because in this model we need
  only storage one number for every loop but it incorporate the information of both positions
  
  
  we abstract from multiloop, bulge loop and internal loop.
  
  - In addition, we take the central position to record these loops.
  
  
- In this slide, I will show the first test result on a test RNA sequence. 
- In this example, we take the multiloop and hairpin loop into account and use the central position.
- the most interesting point from the result is, the 2 conformations with helix index 27 and 38, appear as the first 2 results.
  and if we search further in the list, we can find a combination of the 2 central position at the bottom of the list, namely the records here.
- What does it mean? the solution is in the next slide.  


- in the first linie, we let the energy unlimited, the exponent is the same as last slide, it is about 0.18 [how does one read it?]
- if we set an energy range 20 kcal/mol, so the exponent of the space will be reduced to one third, it amounts to 0.12,
- on the last curve, we're noticing, the exponent value is only 0.036. that means, the runtime grows almost as polynomial curve.

because different RNA have different energy landscape, 
  we can classify the RNA using the information of energy barriers information that are obtained from the software developed within this project, 