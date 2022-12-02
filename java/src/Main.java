import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        
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
}

