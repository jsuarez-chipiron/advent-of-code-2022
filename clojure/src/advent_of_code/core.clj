(ns advent-of-code.core
  (:gen-class)
  (:require [clojure.java.io :as io]))

(defn solve
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

(defn -main
  "I don't do a whole lot ... yet."
  [& args]
  (println (solve 1))
  (println (solve 3)))
