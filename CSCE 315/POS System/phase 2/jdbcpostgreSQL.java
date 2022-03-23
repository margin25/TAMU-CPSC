import java.sql.*;
import java.io.*;  
import java.util.Scanner;  
/*
CSCE 315
9-27-2021 Lab
 */
public class jdbcpostgreSQL {

  //Commands to run this script
  //This will compile all java files in this directory
  //javac *.java
  //This command tells the file where to find the postgres jar which it needs to execute postgres commands, then executes the code
  //Windows: java -cp ".;postgresql-42.2.8.jar" jdbcpostgreSQL
  //Mac/Linux: java -cp ".:postgresql-42.2.8.jar" jdbcpostgreSQL

  //MAKE SURE YOU ARE ON VPN or TAMU WIFI TO ACCESS DATABASE
  public static void main(String args[]){

    //Building the connection with your credentials
    //DONE: update teamNumber, sectionNumber, and userPassword here
     Connection conn = null;
     String teamNumber = "14";
     String sectionNumber = "910";
     String dbName = "csce315" + sectionNumber + "_" + teamNumber + "db";
     String dbConnectionString = "jdbc:postgresql://csce-315-db.engr.tamu.edu/" + dbName;
     String userName = "csce315" + sectionNumber + "_" + teamNumber + "user";
     String userPassword = "drowssap14";

     //Connecting to the database
    try {
        conn = DriverManager.getConnection(dbConnectionString,userName, userPassword);
     } catch (Exception e) {
        e.printStackTrace();
        System.err.println(e.getClass().getName()+": "+e.getMessage());
        System.exit(0);
     }

     System.out.println("Opened database successfully");

     // Trend importing section
    String line="";
    String splitBy=",";
    int trend_id = 1;
    try{
      BufferedReader br = new BufferedReader(new FileReader("FirstWeekSales.csv"));
      line=br.readLine(); //skips first line
      line=br.readLine(); //skips second line
      //sunday
      for(int i=3; i<22; i++){
          line=br.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/2/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-2-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //monday
      line=br.readLine(); //skips first line
      line=br.readLine(); //skips second line
      for(int i=24; i<43; i++){
          line=br.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/3/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-3-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //tuesday 
      line=br.readLine(); //skips first line
      line=br.readLine(); //skips second line
      for(int i=45; i<64; i++){
          line=br.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/4/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-4-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //wednesday 
      line=br.readLine(); //skips first line
      line=br.readLine(); //skips second line
      for(int i=66; i<85; i++){
          line=br.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/5/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-5-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //thursday 
      line=br.readLine(); //skips first line
      line=br.readLine(); //skips second line
      for(int i=87; i<106; i++){
          line=br.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/6/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-6-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //friday 
      line=br.readLine(); //skips first line
      line=br.readLine(); //skips second line
      for(int i=108; i<127; i++){
          line=br.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/7/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-7-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //saturday 
      line=br.readLine(); //skips first line
      line=br.readLine(); //skips second line
      for(int i=129; i<148; i++){
          line=br.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/8/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-8-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }

      // || SECOND WEEK || 
      BufferedReader br2 = new BufferedReader(new FileReader("SecondWeekSales.csv"));
      line=br2.readLine(); //skips first line
      line=br2.readLine(); //skips second line
      //sunday
      for(int i=3; i<22; i++){
          line=br2.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/2/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-9-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //monday
      line=br2.readLine(); //skips first line
      line=br2.readLine(); //skips second line
      for(int i=24; i<43; i++){
          line=br2.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/3/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-10-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //tuesday 
      line=br2.readLine(); //skips first line
      line=br2.readLine(); //skips second line
      for(int i=45; i<64; i++){
          line=br2.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/4/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-11-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //wednesday 
      line=br2.readLine(); //skips first line
      line=br2.readLine(); //skips second line
      for(int i=66; i<85; i++){
          line=br2.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/5/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-12-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //thursday 
      line=br2.readLine(); //skips first line
      line=br2.readLine(); //skips second line
      for(int i=87; i<106; i++){
          line=br2.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/6/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-13-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //friday 
      line=br2.readLine(); //skips first line
      line=br2.readLine(); //skips second line
      for(int i=108; i<127; i++){
          line=br2.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/7/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-14-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //saturday 
      line=br2.readLine(); //skips first line
      line=br2.readLine(); //skips second line
      for(int i=129; i<148; i++){
          line=br2.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/8/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-15-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      // || THIRD WEEK || 
      BufferedReader br3 = new BufferedReader(new FileReader("ThirdWeekSales.csv"));
      line=br3.readLine(); //skips first line
      line=br3.readLine(); //skips second line
      //sunday
      for(int i=3; i<22; i++){
          line=br3.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/2/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-16-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //monday
      line=br3.readLine(); //skips first line
      line=br3.readLine(); //skips second line
      for(int i=24; i<43; i++){
          line=br3.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/3/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-17-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //tuesday 
      line=br3.readLine(); //skips first line
      line=br3.readLine(); //skips second line
      for(int i=45; i<64; i++){
          line=br3.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/4/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-18-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //wednesday 
      line=br3.readLine(); //skips first line
      line=br3.readLine(); //skips second line
      for(int i=66; i<85; i++){
          line=br3.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/5/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-19-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //thursday 
      line=br3.readLine(); //skips first line
      line=br3.readLine(); //skips second line
      for(int i=87; i<106; i++){
          line=br3.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/6/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-20-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //friday 
      line=br3.readLine(); //skips first line
      line=br3.readLine(); //skips second line
      for(int i=108; i<127; i++){
          line=br3.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/7/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-21-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //saturday 
      line=br3.readLine(); //skips first line
      line=br3.readLine(); //skips second line
      for(int i=129; i<148; i++){
          line=br3.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/8/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-22-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      // || FOURTH WEEK || 
      BufferedReader br4 = new BufferedReader(new FileReader("FourthWeekSales.csv"));
      line=br4.readLine(); //skips first line
      line=br4.readLine(); //skips second line
      //sunday
      for(int i=3; i<22; i++){
          line=br4.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/2/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-23-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //monday
      line=br4.readLine(); //skips first line
      line=br4.readLine(); //skips second line
      for(int i=24; i<43; i++){
          line=br4.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/3/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-24-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //tuesday 
      line=br4.readLine(); //skips first line
      line=br4.readLine(); //skips second line
      for(int i=45; i<64; i++){
          line=br4.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/4/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-25-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //wednesday 
      line=br4.readLine(); //skips first line
      line=br4.readLine(); //skips second line
      for(int i=66; i<85; i++){
          line=br4.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/5/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-26-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //thursday 
      line=br4.readLine(); //skips first line
      line=br4.readLine(); //skips second line
      for(int i=87; i<106; i++){
          line=br4.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/6/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-27-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //friday 
      line=br4.readLine(); //skips first line
      line=br4.readLine(); //skips second line
      for(int i=108; i<127; i++){
          line=br4.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/7/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-28-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }
      //saturday 
      line=br4.readLine(); //skips first line
      line=br4.readLine(); //skips second line
      for(int i=129; i<148; i++){
          line=br4.readLine();
          String[] info=line.split(splitBy); // splits by commas 

          System.out.println("trend date = 1/8/22 , menu id = " + Integer.parseInt(info[1]) + ", times ordered = " + Integer.parseInt(info[2]));
         try{
            //create a statement object
            Statement stmt = conn.createStatement();

            //Running a query
             String sqlStatement = "INSERT INTO trends (trend_id, trend_date, menu_id, times_ordered) VALUES (" + trend_id + ", '1-29-2022', " + Integer.parseInt(info[1]) + ", " + Integer.parseInt(info[2]) + ")";
             int result = stmt.executeUpdate(sqlStatement);

             System.out.println("--------------------Query Results--------------------");
             System.out.println(result);
          }catch (Exception e){
               e.printStackTrace();
               System.err.println(e.getClass().getName()+": "+e.getMessage());
               System.exit(0);
          }
          trend_id++;
      }






      try {
        conn.close();
        System.out.println("Connection Closed.");
      } catch(Exception e) {
        System.out.println("Connection NOT Closed.");
      }//end try catch

    }
    catch(IOException e){
        e.printStackTrace();
    } 







     //Inventory importing section


    // String line="";
    // String splitBy=",";
    // String type1="Food";
    // String type2="Bib";
    // String type3="Bottles";
    // String type4="Serving";
    // String type5="Janitorial";


    // try{
    //   BufferedReader br2 = new BufferedReader(new FileReader("First Day Order.csv"));

    //   line=br2.readLine();
    //   line=br2.readLine();
    //   line=br2.readLine();


    //  for(int i=1; i<20; i++){
    //       line=br2.readLine();
    //       String[] info=line.split(splitBy);
    //       System.out.println("inventory ID = " + i + ", item name= " + info[1] + ", type= " + type1 + ", amount= " + Double.parseDouble(info[3]) + ", units= " + info[6]);
    //       try{
    //         //create a statement object
    //         Statement stmt = conn.createStatement();

    //         //Running a query
    //          String sqlStatement = "INSERT INTO inventory (inventory_id, item_name, item_type, amount_available, units) VALUES (" + i + ", '" + info[1] + "', '" + type1 + "', " + Double.parseDouble(info[3]) + ", '" + info[6] + "')";

    //          int result = stmt.executeUpdate(sqlStatement);

    //          System.out.println("--------------------Query Results--------------------");
    //          System.out.println(result);
    //       }catch (Exception e){
    //            e.printStackTrace();
    //            System.err.println(e.getClass().getName()+": "+e.getMessage());
    //            System.exit(0);
    //       }
    //   }

    //   line=br2.readLine();

    //   for(int i=20; i<26; i++){
    //       line=br2.readLine();
    //       String[] info=line.split(splitBy);
    //       System.out.println("inventory ID = " + i + ", item name= " + info[1] + ", type= " + type1 + ", amount= " + Double.parseDouble(info[3]) + ", units= " + info[6]);
    //       try{
    //         //create a statement object
    //         Statement stmt = conn.createStatement();

    //         //Running a query
    //          String sqlStatement = "INSERT INTO inventory (inventory_id, item_name, item_type, amount_available, units) VALUES ("+i+", '"+info[1]+"', '"+type2+"', "+ Double.parseDouble(info[3]) + ", '" + info[6] + "')";

    //          int result = stmt.executeUpdate(sqlStatement);

    //          System.out.println("--------------------Query Results--------------------");
    //          System.out.println(result);
    //       }catch (Exception e){
    //            e.printStackTrace();
    //            System.err.println(e.getClass().getName()+": "+e.getMessage());
    //            System.exit(0);
    //       }
    //   }

    //   line=br2.readLine();

    //   for(int i=26; i<30; i++){
    //       line=br2.readLine();
    //       String[] info=line.split(splitBy);
    //       System.out.println("inventory ID = " + i + ", item name= " + info[1] + ", type= " + type1 + ", amount= " + Double.parseDouble(info[3]) + ", units= " + info[6]);
    //       try{
    //         //create a statement object
    //         Statement stmt = conn.createStatement();

    //         //Running a query
    //          String sqlStatement = "INSERT INTO inventory (inventory_id, item_name, item_type, amount_available, units) VALUES ("+i+", '"+info[1]+"', '"+type3+"', "+ Double.parseDouble(info[3]) + ", '" + info[6] + "')";

    //          int result = stmt.executeUpdate(sqlStatement);

    //          System.out.println("--------------------Query Results--------------------");
    //          System.out.println(result);
    //       }catch (Exception e){
    //            e.printStackTrace();
    //            System.err.println(e.getClass().getName()+": "+e.getMessage());
    //            System.exit(0);
    //       }
    //   }

    //   line=br2.readLine();

    //   for(int i=30; i<43; i++){
    //       line=br2.readLine();
    //       String[] info=line.split(splitBy);
    //       System.out.println("inventory ID = " + i + ", item name= " + info[1] + ", type= " + type1 + ", amount= " + Double.parseDouble(info[3]) + ", units= " + info[6]);
    //       try{
    //         //create a statement object
    //         Statement stmt = conn.createStatement();

    //         //Running a query
    //          String sqlStatement = "INSERT INTO inventory (inventory_id, item_name, item_type, amount_available, units) VALUES ("+i+", '"+info[1]+"', '"+type4+"', "+ Double.parseDouble(info[3]) + ", '" + info[6] + "')";

    //          int result = stmt.executeUpdate(sqlStatement);

    //          System.out.println("--------------------Query Results--------------------");
    //          System.out.println(result);
    //       }catch (Exception e){
    //            e.printStackTrace();
    //            System.err.println(e.getClass().getName()+": "+e.getMessage());
    //            System.exit(0);
    //       }
    //   }

    //   line=br2.readLine();

    //   for(int i=43; i<53; i++){
    //       line=br2.readLine();
    //       String[] info=line.split(splitBy);
    //       System.out.println("inventory ID = " + i + ", item name= " + info[1] + ", type= " + type1 + ", amount= " + Double.parseDouble(info[3]) + ", units= " + info[6]);
    //       try{
    //         //create a statement object
    //         Statement stmt = conn.createStatement();

    //         //Running a query
    //          String sqlStatement = "INSERT INTO inventory (inventory_id, item_name, item_type, amount_available, units) VALUES ("+i+", '"+info[1]+"', '"+type5+"', "+ Double.parseDouble(info[3]) + ", '" + info[6] + "')";

    //          int result = stmt.executeUpdate(sqlStatement);

    //          System.out.println("--------------------Query Results--------------------");
    //          System.out.println(result);
    //       }catch (Exception e){
    //            e.printStackTrace();
    //            System.err.println(e.getClass().getName()+": "+e.getMessage());
    //            System.exit(0);
    //       }
    //   }
    

    //   try {
    //     conn.close();
    //     System.out.println("Connection Closed.");
    //   } catch(Exception e) {
    //     System.out.println("Connection NOT Closed.");
    //   }//end try catch

    // }catch(IOException e){
    //     e.printStackTrace();
    // }



     //Menu importing section

    // String line="";
    // String splitBy=",";

    // try{
    //   BufferedReader br2 = new BufferedReader(new FileReader("MenuKey.csv"));

    //   line=br2.readLine();
    //   line=br2.readLine();


    //   while((line=br.readLine()) != null){
    //     String[] info=line.split(splitBy);

    //     System.out.println("Num= "+Integer.parseInt(info[1])+", name= "+info[2]+ ", price= "+Float.parseFloat(info[info.length-1]));

    //     try{
    //       //create a statement object
    //       Statement stmt = conn.createStatement();

    //       //Running a query
    //        String sqlStatement = "INSERT INTO menu (menu_id, menu_name, price) VALUES ("+Integer.parseInt(info[1])+", '"+info[2]+"', "+Float.parseFloat(info[info.length-1])+")";

    //        int result = stmt.executeUpdate(sqlStatement);

    //        System.out.println("--------------------Query Results--------------------");
    //        System.out.println(result);
    //     }catch (Exception e){
    //          e.printStackTrace();
    //          System.err.println(e.getClass().getName()+": "+e.getMessage());
    //          System.exit(0);
    //     }
        
    //   }

    //   //closing the connection
    //   try {
    //     conn.close();
    //     System.out.println("Connection Closed.");
    //   } catch(Exception e) {
    //     System.out.println("Connection NOT Closed.");
    //   }//end try catch


    // }catch(IOException e){
    //   e.printStackTrace();
    // }

  }//end main
}//end Class
