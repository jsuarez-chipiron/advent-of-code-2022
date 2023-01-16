(ns advent-of-code.core
  (:gen-class)
  (:require [clojure.java.io :as io])
  (:require [clojure.set :as set])
  (:require [clojure.string :as str]))

(defn day1
  "resolve puzzle"
  [n]
  (->>
    (with-open [reader (io/reader "/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day1.txt")]
      (reduce conj [] (line-seq reader)))
    (map #(if (= "" %) 0 (Integer/parseInt %)))
    (partition-by #(= % 0))
    (map #(reduce + %))
    (filter #(not= 0 %))
    (sort >)
    (take n)
    (reduce +)))

(defn day4
  "day 4"
  []
  (->>
    ; read the input file
    (with-open [reader (io/reader "/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day4.txt")]
      (reduce conj [] (line-seq reader)))
    ; expand a list with ranges in the pairs
    (map (fn [j] 
           (map (fn[i]
             (range (Integer/parseInt (first i)) 
               (+ (Integer/parseInt (first (rest i))) 1)))(map #(str/split % #"-")(str/split j #",")))))))

(defn day4-part1
  "day 4"
  []
  (->>
    (day4)
    ; is one set contained in the other or viceversa
    (map #(or
             (set/subset? (set (first %)) (set (first (rest %))))
             (set/subset? (set (first (rest %))) (set (first %)))
           ))
    (map #(if (true? %) 1 0)) 
    (reduce +)))

(defn day4-part2
  "day 4"
  []
  (->>
    (day4)
    ; calculate the intersecction between the list for each row
    (map #(some (set (first %)) (first (rest %))))
    (map #(if (nil? %) 0 1)) 
    (reduce +)))

(defn day6
  "day 6"
  [n]
  (+ (.indexOf (->>
                 (with-open [reader (io/reader "/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day6.txt")]
                   (reduce conj [] (line-seq reader)))
                 (first)
                 (char-array)
                 (seq)
                 (partition n 1)
                 (map #(count (set %)))) n) n))

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (cond
    (= args '("day1"))
      (do
        (println (day1 1))
        (println (day1 3)))
    (= args '("day4"))
      (do
        (println (day4-part1))
        (println (day4-part2)))
    (= args '("day6"))
      (do
        (println (day6 4))
        (println (day6 14)))
    :else (println "error: not valid day")))
