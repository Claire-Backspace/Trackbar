import java.util.ArrayList;
import java.util.Scanner;

interface IParking {
    //打印输出结果
    public void print();

    //检查是否有carType对应的停车位
    //有则返回true 无则返回false
    public boolean addCar(int carType);

    //解析命令行输入的参数
    public static IParams parse() throws Exception {
        int num[] = new int[3];
        Scanner scanner = new Scanner(System.in);
        System.out.println("输入空车位数");
        num[0] = scanner.nextInt();
        num[1] = scanner.nextInt();
        num[2] = scanner.nextInt();

        IParams params = new IParams() {
            //车位数
            @Override
            public int getBig() { return num[0]; }

            @Override
            public int getMedium() { return num[1]; }

            @Override
            public int getSmall() { return num[2]; }

            @Override
            public ArrayList<Integer> getPlanParking() {
                System.out.println("停放车辆");
                ArrayList<Integer> arrayList = new ArrayList<>();
                for (int i = 0; i < 4; i++) {
                    int num = scanner.nextInt();
                    arrayList.add(num);
                }
                return arrayList;
            }

        };
        return params;
    }
}

interface IParams{
    //获取大车位
    public int getBig();
    //获取中车位
    public int getMedium();
    //获取小车位
    public int getSmall();

    //获取停车序列，1为大车、2为中车、3为小车
    public ArrayList<Integer> getPlanParking();
}

public class ParkingSystem implements IParking{
    Integer big;
    Integer medium;
    Integer small;
    public ParkingSystem(Integer big, Integer medium, Integer small) {
        this.big=big;
        this.medium=medium;
        this.small=small;
    }

    public static void main(String[] args) throws Exception {
        for (int j = 0; j < 4; j++) {
            IParams params = IParking.parse();

            ParkingSystem ps = new ParkingSystem(params.getBig(), params.getMedium(), params.getSmall());

            ArrayList<Integer> plan = params.getPlanParking();
            for (int i = 0; i < plan.size(); i++) {
                System.out.print(ps.addCar(plan.get(i)) + " ");
            }
            System.out.println();
//        ps.print();
        }
    }

    @Override
    public void print() {

    }

    @Override
    public boolean addCar(int carType) {
        if(carType==1){
            big--;
            if(big>=0)
                return true;
            else
                return false;
        }
        if(carType==2){
            medium--;
            if(medium>=0)
                return true;
            else
                return false;
        }
        if(carType==3){
            small--;
            if(small>=0)
                return true;
            else
                return false;
        }
        return false;
    }

}