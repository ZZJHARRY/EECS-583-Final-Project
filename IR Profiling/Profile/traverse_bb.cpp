// mypass.cpp
#include <iostream>
#include <algorithm>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/BlockFrequencyInfo.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopIterator.h"

using namespace llvm;
using namespace std;

namespace {
struct mypass : public FunctionPass {
    static char ID;

    mypass() : FunctionPass(ID) {}

    // Specify the list of analysis passes that will be used inside your pass.
    void getAnalysisUsage(AnalysisUsage &AU) const {
        AU.addRequired<BlockFrequencyInfoWrapperPass>(); // Analysis pass to load block execution count
        AU.addRequired<BranchProbabilityInfoWrapperPass>(); // Analysis pass to load branch probability
    }

    bool runOnFunction(Function &F) override{
        // Create objects for each analysis pass
        int i = 0;
        BlockFrequencyInfo &bfi = getAnalysis<BlockFrequencyInfoWrapperPass>().getBFI();
        for (BasicBlock &block: F){
            errs() << "block" << i << " ";
            i++;
            errs() << &(block);
            errs() << "\n";
            errs() << block.getName() << "  frequency :  " << bfi.getBlockFreq(&block).getFrequency();
            errs() << "\n";
            errs() << block.getName() << "  profile count :  " << bfi.getBlockProfileCount(&block);
            errs() << "\n";
        }

        errs() << "DFS Instructions:\n";
        for (const BasicBlock *BB : depth_first(&F)) {
            BB->printAsOperand(errs(), false);
            errs() << "  " << ": BB " << BB->getName() << *BB << "\n";
        } 
        
        // ReversePostOrderTraversal<Function*> RPOT(&F);

        // errs() << "RPO Instructions:\n";
        // for (ReversePostOrderTraversal<Function*>::rpo_iterator I = RPOT.begin(),
        //         E = RPOT.end(); I != E; ++I) {
        //     BasicBlock *BB = *I;
        //     errs() << "  " << ": BB " << BB->getName() << *BB << "\n";
        // }
        return false;
    }
};
}

char mypass::ID = 1;
static RegisterPass<mypass> X("dfs", "Traverse basic block",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
