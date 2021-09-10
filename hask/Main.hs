list = [x * 3 | x <- [1..10], x * 2 <=12 ]
evenUpTo20 = takeWhile (<=20) [10..]
sortal = [4,7,3,9,10,3]
multOf = foldr (*) 2 [2,3,4,5]
multtable =[[x * y | y <- [1..10]] | x<- [1..10]]

addMe :: Int ->Int -> Int
addMe x y = x + y

getListItems :: [Int] -> String
getListItems [] = "Your list is empty"
getListItems (x:[]) = "Your list contains " ++ show x
getListItems (x:y:[]) = "Your list contains " ++ show x ++ " and " ++ show y
getListItems (x:xs) = "The first item is " ++ show x ++ " and the rest are " 
 ++ show xs
 
--54:30 functions as parameters
--56:50 case example
