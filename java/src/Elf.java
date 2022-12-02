import java.util.ArrayList;
import java.util.List;

class Elf{
    private List<Integer> calories;
    private Integer sumCalories=0;
    public void addCalories(Integer calory){
        calories.add(calory);
        sumCalories+=calory;
    }   
    public Integer getSumCalories(){
        return sumCalories;
    }
    Elf(){
        calories=new ArrayList<Integer>();
    }
    Elf(Integer calories){
        this();
        this.addCalories(calories);
    }
    @Override
    public String toString() {
        // TODO Auto-generated method stub
        return super.toString()+calories.toString();
    }
}