module Project4 where
import Control.Monad
import Control.Exception
import Data.List
import System.Timeout
import Data.Either
-- Release 2

data DFA state symbol = DFA
    { alphabet :: [symbol]
    , states   :: [state]
    , initial  :: state
    , transit  :: state -> symbol -> state
    , accept   :: state -> Bool
    }

data ABC = A | B | C deriving (Show, Read, Eq, Ord)

accepts :: DFA state symbol -> [symbol] -> Bool
accepts d = accept d . foldl (transit d) (initial d)
    
atMost2As :: DFA Int ABC
atMost2As = DFA
   { alphabet = [A, B, C]
    , states   = [1,2,3,4]
    , initial  = 1
    , transit  = delta
    , accept   = \s -> s == 2 || s == 3 || s == 1
   }
       where
    delta 1 A = 2
    delta 1 B = 1
    delta 1 C = 1
    delta 2 A = 3
    delta 2 B = 2
    delta 2 C = 2
    delta 3 A = 4
    delta 3 C = 3
    delta 3 B = 3
    delta _ _ = 4

oddAs :: DFA Int ABC
oddAs = DFA
   { alphabet = [A, B, C]
    , states   = [1,2,3]
    , initial  = 1
    , transit  = delta
    , accept   = (== 2)
   }
       where
    delta 1 A = 2
    delta 1 B = 1
    delta 1 C = 1
    delta 2 A = 1
    delta 2 B = 2
    delta 2 C = 2
    delta _ _ = 3
    
hasABC :: DFA Int ABC
hasABC = DFA
   { alphabet = [A, B, C]
    , states   = [1,2,3,4,5]
    , initial  = 1
    , transit  = delta
    , accept   = (== 4)
   }
       where
    delta 1 A = 2
    delta 1 B = 1
    delta 1 C = 1
    delta 2 A = 2
    delta 2 B = 3
    delta 2 C = 1
    delta 3 A = 2
    delta 3 B = 1
    delta 3 C = 4
    delta 4 A = 4
    delta 4 B = 4
    delta 4 C = 4
    delta _ _ = 5


extra_credit = True


multiplex :: DFA s1 a1 -> DFA s2 a2 -> DFA (Int) ABC
multiplex d1 d2 = DFA 
   { alphabet  = [A,B,C]
    , states   = [2]
    , initial  = 1
    , transit  = delta
    , accept   = (== 4)
   }
    where
    delta 1 A = 2
    delta 1 B = 1
    delta 1 C = 1
    delta 2 A = 2
    delta 2 B = 3
    delta 2 C = 1
    delta 3 A = 2
    delta 3 B = 1
    delta 3 C = 4
    delta 4 A = 4
    delta 4 B = 4
    delta 4 C = 4
    delta _ _ = 5






































