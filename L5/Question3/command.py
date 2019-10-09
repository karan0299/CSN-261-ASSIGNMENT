from ete3 import Tree
t = Tree.from_parent_child_table([line.split() for line in open("graph.txt")] )
# import dendropy
# tree1 = dendropy.Tree(stream=open("graph.tre"), schema="newick")
f = open("newick.nh", "w")
f.write(t.write());