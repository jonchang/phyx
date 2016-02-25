/*
 * seqgen.h
 *
 *  Created on: Jun 23, 2015
 *      Author: joe
 */

#ifndef _SEQGEN_H_
#define _SEQGEN_H_

#include <random>

#include "sequence.h"
#include "tree.h"

class SequenceGenerator {

private:
    // constant values
    int seqlen;
    vector <double> basefreqs;
    vector < vector <double> > rmatrix;
    Tree * tree;
    int nreps;
    int seed;
    string Ancestor;
    static map<char, int> nucMap;
    bool showancs;
    
    map <Node *, string> seqs;
    
    vector<Sequence> res;
    
    void preorder_tree_traversal (Tree * tree);
    vector < vector <double> > calculate_q_matrix ();
    vector < vector <double> > calculate_p_matrix (vector < vector <double> > QMatrix, float br);
    string simulate_sequence (string const& anc, vector < vector <double> >& Matrix);
    void generate_random_sequence ();
    //void TakeInTree ();
    mt19937 generator;
    float get_uniform_random_deviate ();
//    vector<Node *> nodes; // unused


public:
    SequenceGenerator ();
    SequenceGenerator (int const &seqlenth, vector <double> const& basefreq,
        vector < vector<double> >& rmatrix, Tree * tree, bool const& showancs, 
        int const& nreps, int const & seed);
    vector<Sequence> get_sequences ();
    //Node * PreOrder(int); // not used
    
    
    //virtual ~SEQGEN();
};

#endif /* _SEQGEN_H_ */