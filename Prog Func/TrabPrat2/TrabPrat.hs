module TrabPrat where
import System.Exit (exitSuccess)
import System.Process (system)
import System.IO (readFile, IOMode(WriteMode, ReadWriteMode), withFile, hPutStr, hGetContents, hPutStrLn, SeekMode(AbsoluteSeek), hSeek)
import Data.Maybe (mapMaybe)
import Text.Read (readMaybe)
import Data.List (groupBy, sortBy, intersect, intercalate)
import Data.Map (Map)
import qualified Data.Map as Map
import Data.Set (Set)
import qualified Data.Set as Set
import Control.Monad (forM)
import Control.Exception (catch, IOException)


-- type synoyms
type Day = Int
type Room = Int
type StudentID = String
type SubjectID = Int

type SubjectMap = Map SubjectID [StudentID]
type SubjectGraph = Map SubjectID (Set SubjectID)
type ExamSchedule = [(SubjectID, Day)]

-- Main function (executes menu)
main :: IO ()
main = menu

-- Menu function
menu :: IO()
menu =  do
    system "cls"                                                       -- clears screen       
    putStrLn "/ / / / / / MENU / / / / / /"                            -- prompt to present available options to user
    putStrLn "(1)   Criar ficheiro com escalonamento dos exames"
    putStrLn "(2)   Apresentar incompatibilidades"
    putStrLn " "
    putStrLn "(0)   Encerrar o programa"
    putStrLn "Selecione uma opçao:"
    input <- getLine                                                 -- asks user for input
    case input of                                                    -- case clause with input to call function(s) needed
        "1" -> tar1
        "2" -> tar2
        "0" -> exitSuccess
        _ -> doesntExist input

readFileWords :: FilePath -> IO [String]           -- takes in a file path and returns a list with the words in that file
readFileWords path = do
  contents <- readFile path
  return (words contents)

tar1:: IO ()                                       -- function that creates file with the exam scheduling
tar1 = do
  putStrLn "Introduza o número de dias disponíveis: "
  days <- readLn
  putStrLn "Introduza o número de salas disponíveis: "
  rooms <- readLn
  contents <- readFile "inscricoes.txt"
  let inscr = words contents
      highNumber = findHighestNumber inscr
  case highNumber of
    Just number -> if number > days * rooms
                     then putStrLn "Nao é possível realizar os exames com essas condiçoes"
                     else do
                      putStrLn "É possível!"
                      ucsGrupo <- createSubjectMap "inscricoes.txt"
                      writeSubjectGroups ucsGrupo "divisaoUcs.txt"
                      let examSchedule = createExamSchedule ucsGrupo days rooms
                      writeExamSchedule examSchedule ucsGrupo "calendarioExames.txt"
    Nothing -> putStrLn "Nao foi possível obter o número mais alto."

findHighestNumber :: [String] -> Maybe Int         -- finds the highest number in list (used to determine how many subjects there are)
findHighestNumber strings = case numbers of
  [] -> Nothing
  _ -> Just (maximum numbers)
  where
    numbers = mapMaybe readMaybe strings

parseLine :: String -> (StudentID, SubjectID)      -- takes a line from the input file and parses it into a tuple (StudentID, SubjectID)
parseLine line =
  case words line of
    [student, subject] -> (student, read subject)
    _ -> error "Formato de linha inválido!"

createSubjectMap :: FilePath -> IO SubjectMap      -- This function reads the contents of the input file and constructs a SubjectMap ()
createSubjectMap filePath = do
  contents <- readFile filePath
  let linesList = lines contents
  let subjectList = map parseLine linesList
  let subjectMap = foldr insertIntoMap Map.empty subjectList
  return subjectMap

insertIntoMap :: (StudentID, SubjectID) -> SubjectMap -> SubjectMap       -- inserts the student ID into the list of students enrolled in the corresponding subject ID
insertIntoMap (student, subject) = Map.insertWith (++) subject [student]

writeSubjectGroups :: SubjectMap -> FilePath -> IO ()       -- writes the subject groups to the specified file (divisaoUcs.txt)
writeSubjectGroups subjectMap filePath = do
  withFile filePath WriteMode $ \handle ->
    let formattedGroups = Map.toList subjectMap
        formattedLines = map formatLine formattedGroups
        groupsContent = unlines formattedLines
    in hPutStr handle groupsContent

formatLine :: (SubjectID, [StudentID]) -> String   -- takes a subject ID and a list of students and formats them as a string
formatLine (subject, students) =
  show subject ++ " " ++ unwords students

createExamSchedule :: SubjectMap -> Int -> Int -> ExamSchedule    -- creates the schedule for the exams
createExamSchedule subjectMap numDays numRooms =
  let subjects = Map.keys subjectMap
      numSubjects = length subjects
      numExamDays = max 1 (ceiling (fromIntegral numSubjects / fromIntegral numRooms))
      examDays = take numSubjects $ cycle [1..numExamDays]
  in zip subjects examDays

writeExamSchedule :: ExamSchedule -> SubjectMap -> FilePath -> IO ()    -- writes the exam schedule to a file
writeExamSchedule examSchedule subjectMap filePath =
  withFile filePath WriteMode $ \handle -> do
    let formattedLines = map (formatLineWithIncompatibilities subjectMap examSchedule) [1..maximumDay]
        scheduleContent = unlines formattedLines
    hPutStr handle scheduleContent
  where
    maximumDay = maximum (map snd examSchedule)

formatLineWithIncompatibilities :: SubjectMap -> ExamSchedule -> Day -> String    -- formats the lines to be written to the schedule file 
formatLineWithIncompatibilities subjectMap examSchedule day =
  let subjectsOnDay = [subject | (subject, d) <- examSchedule, d == day]
      incompatibilities = countStudentsWithMultipleExams subjectMap subjectsOnDay
  in unwords (map show subjectsOnDay) ++ " " ++ show incompatibilities

countStudentsWithMultipleExams :: SubjectMap -> [SubjectID] -> Int
countStudentsWithMultipleExams subjectMap subjects =
  let students = concat [Map.findWithDefault [] subject subjectMap | subject <- subjects]
      studentCounts = Map.fromListWith (+) [(student, 1) | student <- students]
      studentsWithMultipleExams = Map.size (Map.filter (> 1) studentCounts)
  in studentsWithMultipleExams

countOccurrences :: Ord a => [a] -> a -> Int
countOccurrences list element = length (filter (== element) list)

tar2 :: IO ()                                      -- asks user for UCs and calculates incompatibilites
tar2 = do
  contents <- readFile "inscricoes.txt"
  let inscr = words contents
  ucsGrupo <- createSubjectMap "inscricoes.txt"
  writeSubjectGroups ucsGrupo "divisaoUcs.txt"
  putStrLn "Introduza a primeira UC: "
  subject1 <- readSubjectID
  putStrLn "Introduza a segunda UC: "
  subject2 <- readSubjectID
  let incompatibility = countIncompatibilities ucsGrupo (subject1, subject2)
  putStrLn $ "Incompatibilidade entre as UCS " ++ show subject1 ++ " e " ++ show subject2 ++ ": " ++ show incompatibility

countIncompatibilities :: SubjectMap -> (SubjectID, SubjectID) -> Int     -- counts incompatibilities between 2 UCs
countIncompatibilities subjectMap (subject1, subject2) =
  let students1 = Map.findWithDefault [] subject1 subjectMap
      students2 = Map.findWithDefault [] subject2 subjectMap
  in length (filter (`elem` students2) students1)

readSubjectID :: IO SubjectID
readSubjectID = do
  input <- getLine
  case readMaybe input of
    Just subjectID -> return subjectID
    Nothing -> do
      putStrLn "Erro: O ID da UC fornecido é inválido."
      readSubjectID `catch` handleReadException

createSubjectGraph :: IO SubjectMap -> IO SubjectGraph      -- creates a graph where the dots are UCs and the lines bewtween are incompatibilities
createSubjectGraph subjectMapIO = do
  subjectMap <- subjectMapIO
  let subjects = Map.keys subjectMap
  edges <- forM subjects $ \s1 -> do
    let students1 = Map.findWithDefault [] s1 subjectMap
    forM subjects $ \s2 -> do
      let students2 = Map.findWithDefault [] s2 subjectMap
      let hasCommonStudents = not (null (students1 `intersect` students2))
      return (s1, s2, hasCommonStudents)
  let subjectGraph = foldr insertEdge Map.empty (concat edges)
  return subjectGraph
  where
    insertEdge (s1, s2, hasCommonStudents) graph =
      if hasCommonStudents
        then Map.insertWith Set.union s1 (Set.singleton s2) graph
        else graph


-- Error handling
doesntExist :: String -> IO ()
doesntExist opt =
  putStrLn $ "A opção " ++ opt ++ " não existe"

handleReadException :: IOError -> IO SubjectID
handleReadException _ = do
  putStrLn "Erro ao ler o ID da UC."
  readSubjectID
