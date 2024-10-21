# Lecture 21.oct - Type systems general introduction 

Concurrency can be automatically be checked with a type system 

Formal methods: system model validation through mathematical expressions. Then use pure math to validate the program. 

Why types?
- Detect errors => compiler will detect errors for you based on types 
- Abstraction => hide memory implementation details
- Documentation => a good way to express intended behavior 

"Well-typed programs cannot go wrong" - Robin Milner
- What is a type? An expression of a type that always evaluates to a value of the given type 
- What are behavior types? Abstraction of a behavior that is given for the type 
- Static systems checking => at compile time
- Dynamic systems check => at runtime
- Strong vs. weak typing => Strong typing aims to cover all types of errors
- Examples of errors:
  - Applying operators that are not defined on all inputs 
  - Well-typed system can also detect deadlocks 


Type soundness => if the program adheres to the types at compile time, then certain errors do not occur at runtime 
- Formalized either as reachability or reduction 

Type analysis: 
- Relation between types and logic 

## Creating a simple type system 

e:= n E Z | true | false | e + e | e /\ e |

Type syntax:
T ::= Bool | Int

Type judgement: 
- To evaluate that an expression holds to a type 
- Symbol for judgement har a line down with small line in the middle to the left 


Typing rules: 
- A typing rule contains one conclusion, and a list of premises. 
- Eah conclusion and ........

Typing tree:
- Tree where each node is a type rule application on a concrete expression. 
- A tree is closed if all leaves are stemming from axioms 
  - This means that we can evaluate them 

Evaluation: 
-  

Literals and evaluation: 
-

Preservation: 
- If an expression can evaluate then the result is well-typed

Progress: 
- If a well-typed expression is not successfully terminated, then it can evaluate 

## Typing Environment and sub typing 

- Need variables 
- A type environment is a map from variables to types. 
  - Noted with L flipped upside down 
- A variable can also be mapped to an undefined type 
- Type judgement include the type environment 


Sub typing: 
- Every type is a subtype of itself 


Types for statements: 
- Unit type is used to type statement 
- Skip is a well-typed axiom 
- We can type declarations, branching and assignments 
- Scooping is also typed, where the scoped environment would contain different mapping


Typing channels: 
- Channel of a type is also a type in itself 
- Type channels based on what is allowed: read, write or both