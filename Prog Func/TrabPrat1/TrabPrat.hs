module TrabPrat where
import System.Exit (exitSuccess)
import System.Process (system)

main :: IO ()
main = menu                                                             -- main funtion (executes menu)

menu :: IO()
menu =  do                                                              -- menu function
    system "cls"                                                        -- clears screen       
    putStrLn "/ / / / / / MENU / / / / / /" 
    putStrLn "1. Alunos inscritos em cada UC"                           -- prompt to present available options to user
    putStrLn "2. Inscriçoes de cada aluno"
    putStrLn "3. Alunos inscrito numa UC em específico"
    putStrLn "4. Inscriçoes de um aluno específico"
    putStrLn "5. Encerrar o programa"
    putStrLn "Selecione uma opçao:" 
    input <- getLine                                                    -- asks user for input
    case input of                                                       -- case clause with input to call function(s) needed
        "1" -> tar1
        "2" -> tar2
        "3" -> tar3
        "4" -> tar4
        "5" -> exitSuccess

fileSplit :: FilePath -> IO [[String]]                                  -- function that takes in a file path and returns a list with 
fileSplit filePath = do                                                 -- the words in that file 
  -- Read the contents of the file
  fileContents <- readFile filePath                                     -- reads file
  -- Split the contents into lines
  let linesList = lines fileContents                                    -- divides content into lines
  -- Split each line into words
  let wordsList = map words linesList                                   -- divides lines into words
  -- Return the list of words for each line
  return wordsList                                                      -- returns wordlist of that file

getUcs :: [[String]] -> [[String]] -> [[String]] -> String -> [String]  -- function that returns a list with ONLY the UC name
getUcs inscr ucs listaAl option =
  case option of                                                        -- case clause for each of the 4 UCs
    "pf" -> [head ucs !! 2 ++ " " ++ head ucs !! 3]
    "c" -> [ucs !! 1 !! 2]
    "t" -> [ucs !! 2 !! 2]
    "f" -> [ucs !! 3 !! 2]

getAl :: [[String]] -> [[String]] -> [[String]] -> String -> [String]   -- function that returns a list with ONLY the student name
getAl inscr ucs listaAl option =
  case option of                                                        -- case clause for each of the 4 students
    "al001" -> [head listaAl !! 2 ++ " " ++ head listaAl !! 3]
    "al002" -> [listaAl !! 1 !! 2 ++ " " ++ listaAl !! 1 !! 3]
    "al003" -> [listaAl !! 2 !! 2 ++ " " ++ listaAl !! 2 !! 3]
    "al004" -> [listaAl !! 3 !! 2 ++ " " ++ listaAl !! 3 !! 3]


tar1 :: IO()                                                            -- function that corresponds to task 1 (print students in UCs)
tar1 = do
    system "cls"                                                        -- clears screen
    ucs <- fileSplit "ucs.txt"
    listaAl <- fileSplit "listaalunos.txt"
    inscr <- fileSplit "inscricoes.txt"
    -- print students in programacao funcional using the functions defined above (getUCs and GetAl)
    let progFunc = getUcs inscr ucs listaAl "pf" ++ getAl inscr ucs listaAl "al001" ++ getAl inscr ucs listaAl "al002"
    print progFunc
    -- print students in compiladores using the functions defined above (getUCs and GetAl)
    let comp = getUcs inscr ucs listaAl "c" ++ getAl inscr ucs listaAl "al001" ++ getAl inscr ucs listaAl "al002" ++ getAl inscr ucs listaAl "al003"
    print comp
    -- print students in topicos using the functions defined above (getUCs and GetAl)
    let topicos = getUcs inscr ucs listaAl "t" ++ getAl inscr ucs listaAl "al004"
    print topicos
    -- print students in fisica using the functions defined above (getUCs and GetAl)
    let fisica = getUcs inscr ucs listaAl "f"
    print fisica
    system "pause"                                                      -- pauses system until further input
    main                                                                -- loops back to main

tar2 :: IO()                                                            -- function that corresponds to task 2 (print students' enrolled UCs)
tar2 = do
    system "cls"                                                        -- clears screen
    ucs <- fileSplit "ucs.txt"
    listaAl <- fileSplit "listaalunos.txt"
    inscr <- fileSplit "inscricoes.txt"
    -- print UCs in which al001 is enrolled using the functions defined above (getUCs and GetAl)
    let al001 = getAl inscr ucs listaAl "al001" ++ getUcs inscr ucs listaAl "pf" ++ getUcs inscr ucs listaAl "c"
    print al001
    -- print UCs in which al002 is enrolled using the functions defined above (getUCs and GetAl)
    let al002 =  getAl inscr ucs listaAl "al002" ++ getUcs inscr ucs listaAl "pf" ++ getUcs inscr ucs listaAl "c"
    print al002
    -- print UCs in which al003 is enrolled using the functions defined above (getUCs and GetAl)
    let al003 =  getAl inscr ucs listaAl "al003"  ++ getUcs inscr ucs listaAl "c"
    print al003
    -- print UCs in which al004 is enrolled using the functions defined above (getUCs and GetAl)
    let al004 =  getAl inscr ucs listaAl "al004" ++ getUcs inscr ucs listaAl "t"
    print al004
    system "pause"                                                      -- pauses system until further input
    main                                                                -- loops back to main

tar3 :: IO()                                                            -- function that corresponds to task 3 (print students in specific UC)
tar3 = do
    system "cls"                                                        -- clears screen
    ucs <- fileSplit "ucs.txt"
    listaAl <- fileSplit "listaalunos.txt"
    inscr <- fileSplit "inscricoes.txt"
    putStrLn "1. Programaçao Funcional"                                 -- prompt to present available UCs to user
    putStrLn "2. Compiladores"
    putStrLn "3. Tópicos"
    putStrLn "4. Física"
    putStrLn "Escolha a cadeira que pretende:"                          -- asks user for input
    option <- getLine   
    case option of                                                      -- case clause with option selected by the user to call a specific function 
    -- print students in programacao funcional using the functions defined above (getUCs and GetAl)
        "1" -> let progFunc = getUcs inscr ucs listaAl "pf" ++ getAl inscr ucs listaAl "al001" ++ getAl inscr ucs listaAl "al002"
                in print progFunc
    -- print students in compiladores using the functions defined above (getUCs and GetAl)
        "2" ->  let comp = getUcs inscr ucs listaAl "c" ++ getAl inscr ucs listaAl "al001" ++ getAl inscr ucs listaAl "al002" ++ getAl inscr ucs listaAl "al003"
                in print comp
    -- print students in topicos using the functions defined above (getUCs and GetAl)
        "3" -> let topicos = getUcs inscr ucs listaAl "t" ++ getAl inscr ucs listaAl "al004"
                in print topicos
    -- print students in fisica using the functions defined above (getUCs and GetAl)
        "4" -> let fisica = getUcs inscr ucs listaAl "f"
                in print fisica
    system "pause"                                                      -- pauses system until further input
    main                                                                -- loops back to main

tar4 :: IO()                                                            -- function that corresponds to task 4 (print a specific student enrolled UCs)
tar4 = do
    system "cls"                                                        -- clears screen
    ucs <- fileSplit "ucs.txt"
    listaAl <- fileSplit "listaalunos.txt"
    inscr <- fileSplit "inscricoes.txt"
    putStrLn "1. al001 - Rui Silva"                                     -- prompt to present available students to user
    putStrLn "2. al002 - Maria Silva"
    putStrLn "3. al003 - Tiago Silva"
    putStrLn "4. al004 - Sofia Silva"
    putStrLn "Escolha o aluno que pretende:"                            -- asks user for input
    option <- getLine
    case option of                                                      -- case clause with option selected by the user to call a specific function
    -- print UCs in which al001 is enrolled using the functions defined above (getUCs and GetAl) 
        "1" -> let al001 = getAl inscr ucs listaAl "al001" ++ getUcs inscr ucs listaAl "pf" ++ getUcs inscr ucs listaAl "c"
                in print al001
    -- print UCs in which al002 is enrolled using the functions defined above (getUCs and GetAl)
        "2" -> let al002 =  getAl inscr ucs listaAl "al002" ++ getUcs inscr ucs listaAl "pf" ++ getUcs inscr ucs listaAl "c"
                in print al002
    -- print UCs in which al003 is enrolled using the functions defined above (getUCs and GetAl)
        "3" -> let al003 =  getAl inscr ucs listaAl "al003"  ++ getUcs inscr ucs listaAl "c"
                in print al003
    -- print UCs in which al004 is enrolled using the functions defined above (getUCs and GetAl)
        "4" -> let al004 =  getAl inscr ucs listaAl "al004" ++ getUcs inscr ucs listaAl "t"
                in print al004
    system "pause"                                                      -- pauses system until further input
    main                                                                -- loops back to main