import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public abstract class FileParser<T>{
    public abstract T parse(T currentItem,List<T> toReturn,String lineToParse);
    public List<T> toList(String fileName) {
        final List<T> toReturn=new ArrayList<>();
        File inputFile = new File(fileName);
        try (BufferedReader br = new BufferedReader(new FileReader(inputFile))) {
            String line;
            T curr=null;
            while ((line = br.readLine()) != null) {
                curr=parse(curr,toReturn,line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return toReturn;
    }
}