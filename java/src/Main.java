import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.OptionalInt;
import java.util.Stack;

import javax.security.auth.x500.X500Principal;

public class Main {
    public static void firstDay(String[] args){
        List<Elf> elfs=new FileParser<Elf>(){
            @Override
            public Elf parse(Elf currentElf,List<Elf> toReturn,String lineToParse) {
                if (lineToParse.isEmpty()){
                    return null;
                }
                if (currentElf==null){
                    currentElf=new Elf();
                    toReturn.add(currentElf);
                }
                final Integer calories=Integer.parseInt(lineToParse);
                currentElf.addCalories(calories);
                return currentElf;
            }
        }
        .toList(args[0]);

        //Max calories
        System.out.println(elfs.stream()
        .parallel()
        .map(Elf::getSumCalories)
        .reduce(0,Integer::max));

        //Top 3 max calories
        LinkedList<Integer> top3Elf=new LinkedList<Integer>(Arrays.asList(0,0,0));
        for(Elf el:elfs){
            for(int i=0;i<3;i++){
                if(top3Elf.get(i)<el.getSumCalories()){
                    top3Elf.add(i,el.getSumCalories());
                    break;
                }
            }
            
        }
        System.out.println(top3Elf.get(0)+top3Elf.get(1)+top3Elf.get(2));
    }
    public static void secondDay(String[] args){
        Integer WIN=6, DRAW=3,LOSE=0;
        Integer ROCK=1, PAPER=2,SCISSORS=3;
        Map<String,Integer> ruleScoring=new HashMap<>(){{
                put("A X", DRAW+ROCK);//ROCK - ROCK
                put("A Y", WIN+PAPER);//ROCK - PAPER
                put("A Z", LOSE+SCISSORS);//ROCK - SCISSORS
                put("B X", LOSE+ROCK);//PAPER - ROCK
                put("B Y", DRAW+PAPER);//PAPER - PAPER
                put("B Z", WIN+SCISSORS);//PAPER - SCISSORS
                put("C X", WIN+ROCK);//SCISSORS - ROCK
                put("C Y", LOSE+PAPER);//SCISSORS - PAPER
                put("C Z", DRAW+SCISSORS);//SCISSORS - SCISSORS
            }};

        System.out.println(new FileParser<String>(){
            @Override
            public String parse(String current,List<String> toReturn,String lineToParse) {
                toReturn.add(lineToParse);
                return lineToParse;
            }
        }
        .toList(args[0])
        .stream()
        .mapToInt(ruleScoring::get)
        .reduce(Integer::sum)
        .getAsInt());
    }
    public static void main(String[] args) {
        secondDay(args);
    }
}

