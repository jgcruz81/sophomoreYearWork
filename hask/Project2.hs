module Project2 where

num = [0.0]
doGuessing :: Int->[Double]        
doGuessing col 
    | col > 1 = concat(replicate col num)
    | col == 1 = num
    | col == 0 = []
zero :: Int -> Int -> [[Double]]
zero row col
   | row >= 1 = replicate row (doGuessing col)
   | row == 0 = []



idMatrix :: Int -> [[Int]]
idMatrix n =
  let xs = [1 .. n]
  in (\x -> fromEnum.(x ==) <$> xs) <$> xs
  

cc :: [Int] -> [Double]
cc [] = []
cc (x:xs) = (fromIntegral x :: Double) : cc xs  

                  
ident :: Int -> [[Double]]
ident n = map cc (idMatrix n)



rlength :: [[Double]] -> Int
rlength x = length x
clength :: [Double] -> Int
clength x = length x

gimmehead :: [[Double]] -> [Double]
gimmehead x = head x

grab :: [[Double]]->Int
grab a = min (rlength a) (clength (gimmehead a))

reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]

yeet :: [[Double]] -> Int -> [Double]
yeet [] _ = []
yeet x a
   | a > 0 = (x!!(a-1))!!(a-1) : yeet x (a-1)
   | otherwise = [] 
diag :: [[Double]] -> [Double]
diag x = reverse (yeet x (grab x))



add :: [[Double]] -> [[Double]] -> [[Double]]
add [] [] = [] 
add (x:xs) (y:ys) = zipWith (+) x y : add xs ys



transp :: [[Double]] -> [[Double]]
transp ([]:_) = []
transp x = (map head x) : transp (map tail x)
----------------
data Sparse = Sparse Int Int [(Int,[(Int,Double)])]
    deriving (Show, Eq)

idsparse :: Int->Int-> [(Int,[(Int,Double)])]
idsparse 0 0 = []
idsparse place x
   | x < place = [(x,[(x,1.0)])] ++ idsparse place (x+1)
   | otherwise = []
sident :: Int -> Sparse
sident x = Sparse x x (idsparse x 0)



rep :: Int -> a -> [a] -> [a]
rep n item ls = a++(item:b) where 
   (a, (_:b)) = splitAt n ls
second :: [Double] -> (Int,Double)-> [Double]
second a (y,z) = (rep y z a)
third :: [Double] -> Int-> [(Int,Double)]-> [Double]
third a size b
   | size > 0 = third (second a (b!!(size-1))) (size-1) b
   | otherwise = a
--which row
getSize :: (Int,[(Int,Double)]) -> Int
getSize (a,b) = length b
fourth :: [[Double]]-> (Int,[(Int,Double)])-> [[Double]]
fourth a (b,c) = rep b (third (a!!b) (getSize (b,c)) c) a
final :: [[Double]] -> Int -> [(Int,[(Int,Double)])]->[[Double]]
final a size c
   | size > 0 = final (fourth a (c!!(size-1))) (size-1) c
   | otherwise = a
sdiag :: Sparse -> [Double]
sdiag (Sparse a b c) = diag (final (zero a b) (length c) c)




sadd :: Sparse -> Sparse -> Sparse
sadd = undefined










