'''Algo tester'''

from os import *
import time
import readfiles as rf

def antAlgo():
    
    system('g++ TSPConstructor.cpp -o TSPConstructor')
    system('./TSPConstructor')
    system('g++ antal.cpp -o antal')
    system('g++ antalElitist.cpp -o antalElitist')
    system('g++ antalRank.cpp -o antalRank')

    #t1 = time()
    
    system('./antal')
    system('./antalElitist')
    system('./antalRank')

    rf.cityReadSACO()
    rf.cityReadElitist()
    rf.cityReadRank()


if __name__ =='__main__':
    antAlgo()
    
    

    

