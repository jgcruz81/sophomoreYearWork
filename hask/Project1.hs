module Project1 where
import Data.List
import System.IO

div7or9 :: Integer -> Bool
div7or9  x
   | x `mod` 7 == 0 = True
   | x `mod` 9 == 0 = True
   | otherwise = False

echo :: [Char] -> [Char]
echo x = concat (map (replicate 2) x)

echons :: [Char] -> [Char]
echons x = concat (map valueOf x)

valueOf :: Char -> [Char]
valueOf ' ' = [' ']
valueOf x = replicate 2 x


countEvens :: [Integer] -> Integer
countEvens [] = 0
countEvens  (x:xs)
     |(x `mod` 2) == 0 = 1 + countEvens xs
     |otherwise = countEvens xs


centroid :: [(Double, Double)] -> (Double, Double)
centroid x = zit (avgX x) (avgY x)
    
pointy :: (t, Double) -> Double
pointy (_, i) = i
pointx :: (Double, t) -> Double
pointx (i, _) = i

pointsy :: [(t, Double)] -> [Double]
pointsy x = map pointy x
pointsx :: [(Double,t)] -> [Double]
pointsx xs = map pointx xs

averageFrac :: (Fractional a) => [a] -> a
averageFrac xs = sum xs / fromIntegral (length xs)

avgY p = averageFrac (pointsy p)
avgX p = averageFrac (pointsx p)

zit :: x->y->(x,y)
zit x y = (x,y)

 
hs :: Integer -> Integer
hs n
  | even n = n `div` 2
  | otherwise = 3 * n + 1

my_length :: [Integer] -> Integer
my_length [] = 0
my_length (_:xs) = 1 + my_length xs

hail :: Integer -> [Integer]
hail = takeWhile (/= 1).iterate hs

hailstone :: Integer -> Integer
hailstone 0 = 0
hailstone 1 = 1
hailstone x = (my_length (hail x)) + 1 













