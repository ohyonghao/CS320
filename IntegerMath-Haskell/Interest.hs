-- My First Haskell program
data Expr 
    = Value Int -- Value takes an integer value
    | Add Expr Expr -- Binary takes two expressions
    | Sub Expr Expr -- Binary takes two expressions
    | Mul Expr Expr -- Binary takes two expressions
    | Div Expr Expr -- Binary takes two expressions
    deriving Show

data IntOnly a
    = Novalue
    | Result a
    deriving (Show, Eq)
fromIntOnly ( Result a ) = a

eval :: Expr -> IntOnly Int
eval ( Value x ) = Result x 
eval ( Add a b ) 
                 | ar == Novalue = Novalue
                 | br == Novalue = Novalue 
                 | otherwise = Result ( fromIntOnly(ar) + fromIntOnly(br) )
                 where ar = eval a
                       br = eval b
eval ( Sub a b ) 
                 | ar == Novalue = Novalue
                 | br == Novalue = Novalue 
                 | otherwise = Result ( fromIntOnly(ar) - fromIntOnly(br) )
                 where ar = eval a
                       br = eval b
eval ( Mul a b ) 
                 | ar == Novalue = Novalue
                 | br == Novalue = Novalue 
                 | otherwise = Result ( fromIntOnly(ar) * fromIntOnly(br) )
                 where ar = eval a
                       br = eval b
eval ( Div a b ) 
                 | ar == Novalue = Novalue
                 | br == Novalue = Novalue 
                 | divisable = Result( fromIntOnly(ar) `div` fromIntOnly(br) )
                 | otherwise = Novalue
                 where ar = eval a
                       br = eval b
                       divisable = fromIntOnly(br) /= 0 && fromIntOnly(ar) `mod` fromIntOnly(br) == 0

-- A lot of repetitive stuff here, is there a way to combine these, perhaps 
-- using composition?
printexpr ( Value x ) = show x
printexpr ( Add a b ) = printex (a, b, "+")
printexpr ( Sub a b ) = printex (a, b, "-")
printexpr ( Mul a b ) = printex (a, b, "*")
printexpr ( Div a b ) = printex (a, b, "/")
printex (a, b, op ) = "(" ++ (printexpr a) ++ op ++ (printexpr b) ++ ")"

-- cartesian product of input list and operators with restrictions on values
x = [(y,z)| 
    y<- [splitAt n l | let l = [(Value 10),(Value 10),(Value 10),(Value 10)], n <- [0..length l ]] ,
    z<- [[x,y,z]|let o = [Add, Sub, Mul, Div],x<-o, y<-o, z<-o],  -- double cartesian product
    eval( expr(y,z)) /= Novalue, 
    0 <= fromIntOnly(eval(expr(y,z))), 
    fromIntOnly(eval(expr(y,z))) < 10 ]

---------------------------------------------------------------------------------------------------------------
-- Build expressions
---------------------------------------------------------------------------------------------------------------
expr (([], [v]   ), _ ) = v
expr (([], (v:vt)), o ) = (o' v (expr( ( [], vt ), or )) )
                       where o' = head o
                             or = tail o
expr (([v], []   ), _ ) = v
expr (((v:vt), []), o ) = (o' (expr( ( vt, [] ), ol )) v )
                       where o' = head o
                             ol = tail o
expr ((l, r ), o ) = o' (expr( ( [], r), or )) (expr( ( l, [] ), ol ))
                  where o' = (head o)
                        ol = take ( length(l) - 1 ) ( tail o )
                        or = drop ( length(l) - 1 ) ( tail o )

-- Do the value check here for 0-9 maybe by passing the tuple from zip, then print with combine
printperline [] = return ()
printperline (x:y) = putStrLn x >> printperline y

-- This puts it all together, produces the string expressions
main  = let combine (x,y) = x ++ "=" ++ (show (fromIntOnly(y))) in  (printperline ( map combine ( ( zip ( map printexpr ex ) ( map eval ex ) ) ) ) )
    where ex = (map expr x)

-- Unit tests for the binary tree

test00 = expr(([], [(Value 1)]), [Add] )
test02 = expr(([], [(Value 1), (Value 2)]), [Add,Add] )

test04 = expr( x !! 3  )
test13 = expr( x !! 13 )
test22 = expr( x !! 40 )
test31 = expr( x !! 60 )
test40 = expr( x !! 75 )

test =  [ (test00), (test02), (test04), (test13), (test22), (test31), (test40) ]
