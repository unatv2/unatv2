// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

#include <stdint.h>

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double SIGCHECK_VERIFICATION_FACTOR = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64_t nTimeLastCheckpoint;
        int64_t nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
        (     0, uint256("0x00000000692c5ed1da2f480cd8d6aa6aa6b16deff49c26bf5a773120328b8b12"))
		(     38, uint256("0x00000000000000022b33f276fea2b1e8f8f25e0ffe28701011b31c514f2b5e3f"))
		(     39, uint256("0x00000000000000044eb74fb875e864d5dc5fc8a05249a3d17d830f0780887bbf"))
		(     49, uint256("0x00000000000000001f32d6777d49295adafb626e1ed05433ffea27eb5aa298b5"))
        ( 15000, uint256("0x0000000000000de93ff723e38ac0eb1f42ed2a6cc265ac450966fb243679d9ce"))
        ( 30000, uint256("0x000000000000147bfd7ec556f8693e1b27d9676fab54f22f4b53433cedb96b86"))
        ( 34000, uint256("0x0000000000004ee9273eacf5df8a0525ecaf062c90aa442d5dcfe51e0f9e8e4b"))
	    ( 100000, uint256("0x00000000000043371be22a64bdd6068fbaabddf64bc9c33a7f8885a966e94f44"))
	    ( 150000, uint256("0x00000000000ea16bc9894e89a6fc17e9074c0cfb133f862c019de20f6949b472"))
		( 200000, uint256("0x0000000000162b22a5ade970009fc88e0edfcbe4108f2bf453a5e9ca4b98a41d"))
        ( 250000, uint256("0x000000000000b8c9646f9c40bf86b12737fa0aaae1deb06eeba223182086bce9"))
        ( 350000, uint256("0x000000000020dfb51cb5c9415849442597777ecac2fe50cfe72809f55ffcf008"))
        ( 450000, uint256("0x00000000000d98ab327b411d9c1efdea4de2ca193990b6eeec4dce0d3d0ea9ad"))
        ( 550000, uint256("0x000000000001e9b6f445778d418edd2221574ef3eea4ed8d4942667fef11065e"))
		( 600000, uint256("0x0db7500498db8d98ea3a6211bc6460ed87acac8fc726c38d8db474f11ee69c40"))
		( 650000, uint256("0x000000000000a05858704d957cc18dc33579e72efa5e2bcb44204d205b9a24b7"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1429510091, // * UNIX timestamp of last checkpoint block
        37149,      // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        10800.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 546, uint256("000000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1338180505,
        16341,
        300
    };

    static MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"))
        ;
    static const CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

    const CCheckpointData &Checkpoints() {
        if (Params().NetworkID() == CChainParams::TESTNET)
            return dataTestnet;
        else if (Params().NetworkID() == CChainParams::MAIN)
            return data;
        else
            return dataRegtest;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex, bool fSigchecks) {
        if (pindex==NULL)
            return 0.0;

        int64_t nNow = time(NULL);

        double fSigcheckVerificationFactor = fSigchecks ? SIGCHECK_VERIFICATION_FACTOR : 1.0;
        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkpoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
