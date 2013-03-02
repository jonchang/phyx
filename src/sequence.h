#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <string>
#include <vector>
using namespace std;



class Sequence{
private:
    string id;
    string seq;
    bool aligned;
    string reverse(string );
    vector<double> qualarr;

public:
    Sequence();
    Sequence(string,string,bool);
    Sequence(string,string);
    bool is_aligned();
    string get_sequence();
    string get_id();
    void set_sequence(string seq);
    void set_id(string id);
    void set_aligned(bool al);
    void set_qualstr(string &,int);
    vector<double> get_qualarr();
    string reverse_complement();
    void perm_reverse_complement();
    string get_fasta();
};
#endif