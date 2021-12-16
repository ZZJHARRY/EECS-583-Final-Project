#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Format.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/Analysis/BlockFrequencyInfo.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include <map>
#include <vector>

using namespace llvm;

namespace
{
    struct mypass : public FunctionPass
    {
        static char ID;
        mypass() : FunctionPass(ID){}
        
        void getAnalysisUsage(AnalysisUsage &AU) const
        {
            AU.addRequired<BlockFrequencyInfoWrapperPass>();    // Analysis pass to load block execution count
            AU.addRequired<BranchProbabilityInfoWrapperPass>(); // Analysis pass to load branch probability
        }

        virtual bool runOnFunction(Function &F) override
        {
            BranchProbabilityInfo &bpi = getAnalysis<BranchProbabilityInfoWrapperPass>().getBPI();
            BlockFrequencyInfo &bfi = getAnalysis<BlockFrequencyInfoWrapperPass>().getBFI();
            float dynop = 0, ialu = 0, falu = 0, mem = 0, biased = 0, unbiased = 0, other = 0;
            BasicBlock *entry = &*F.begin();
            std::map<int, BasicBlock *> bb_index;
            std::vector<int> index{0, 36, 8, 10, 35, 33, 38};
            std::vector<int> order{0, 38, 33, 35, 36, 8, 10};
            for (int i : index){
                bb_index[i] = nullptr;
            }
            int idx = 0;
            for (auto bb : depth_first(&F))
            {
                bb_index[index[idx]] = bb;
                idx++;
            }

            for (int j = 1; j < order.size(); j++){
                bb_index[order[j]]->moveAfter(bb_index[order[j-1]]);
            }
            
            
            return false;
        }
    };
}
char mypass::ID = 0;
static RegisterPass<mypass> X("mypass", "Counts opcodes per functions", false, false);
