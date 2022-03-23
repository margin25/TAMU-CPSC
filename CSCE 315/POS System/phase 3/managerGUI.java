import java.sql.*;
import java.util.Vector;
import java.awt.*;

import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;

/*
  TODO:
  1) [blah]
*/

public class managerGUI extends JFrame implements ActionListener {
    static JFrame manager_frame;
    // static JFrame f;

    public static void main (String[] args) {
        // Building the connection with team database credentials
        Connection conn = null;
        try {
            Class.forName("org.postgresql.Driver");
            conn = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                    "csce315910_14user", "drowssap14");
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
        JOptionPane.showMessageDialog(null, "Opened database successfully");
        // Column names
        String[] menu_columns = { "Menu ID", "Menu Name", "Price" };
        String[] inventory_columns = { "Inventory ID", "Item Name", "Item Type", "Amount Available" };

        Vector<String[]> menu_content = new Vector<String[]>();
        Vector<String[]> inventory_content = new Vector<String[]>();
        try {
            // create a statement object
            Statement stmt = conn.createStatement();
            // create an SQL statement querying 10 menu item names
            String sqlStatement = "SELECT * FROM menu";

            // send statement to DBMS
            ResultSet result = stmt.executeQuery(sqlStatement);

            while (result.next()) {

                String[] row = { result.getString("menu_id"), result.getString("menu_name"),
                        result.getString("price") };
                menu_content.add(row);
            }

        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Error accessing Database.-menu");
        }

        try {
            // create a statement object
            Statement stmt = conn.createStatement();
            // create an SQL statement querying 10 menu item names
            String sqlStatement = "SELECT * FROM inventory";

            // send statement to DBMS
            ResultSet result = stmt.executeQuery(sqlStatement);

            while (result.next()) {

                String[] row = { result.getString("inventory_id"), result.getString("item_name"),
                        result.getString("item_type"), result.getString("amount_available") };
                inventory_content.add(row);
            }

        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Error accessing Database.- inventory");
        }

        String[][] menu_data = new String[menu_content.size()][3];
        for (int i = 0; i < menu_content.size(); ++i) {
            menu_data[i] = menu_content.elementAt(i);
        }

        String[][] inventory_data = new String[inventory_content.size()][4];
        for (int i = 0; i < inventory_content.size(); ++i) {
            inventory_data[i] = inventory_content.elementAt(i);

        }

        // create and set dimensions of the managers frame
        manager_frame = new JFrame("Manager GUI");
        manager_frame.setSize(1200, 800);
        manager_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // create first tabs object
        JTabbedPane tabs = new JTabbedPane();

        // create icon
        // ImageIcon icon = new ImageIcon("layne.jpg");

        // create first tab with w/ no icon
        JPanel order_trends = new JPanel();
        tabs.addTab("Ordering Trends", order_trends);

        // create second tab with w/ no icon
        JPanel inv_forecasting = new JPanel();
        tabs.addTab("Inventory Forecasting", inv_forecasting);

        // create third tab with w/ no icon
        JPanel weekly_profit = new JPanel();
        tabs.addTab("Weekly Profit", weekly_profit);

        // create fourth tab with w/ no icon
        JPanel p_inv_management = new JPanel();
        JLabel l_tab4 = new JLabel("Inventory");
        p_inv_management.add(l_tab4, BorderLayout.NORTH);
        JPanel p_inv_edit = new JPanel();
        JSplitPane sp_inv_split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, p_inv_management, p_inv_edit);

        tabs.addTab("Inventory Management", sp_inv_split);

        // Modify height and width of split pane

        sp_inv_split.setDividerLocation(800);
        Dimension min_size2 = new Dimension(590, 390);
        p_inv_management.setMinimumSize(min_size2);
        p_inv_edit.setMinimumSize(min_size2);

        // Create table for inventory management
        JTable t_inventory = new JTable(inventory_data, inventory_columns);
        p_inv_management.add(new JScrollPane(t_inventory));
        t_inventory.setEnabled(false);

        // Add areatext and specify size : Mualla
        JTextArea t_inv_id = new JTextArea();
        t_inv_id.setLineWrap(true);
        t_inv_id.setSize(100, 50);
        t_inv_id.setForeground(Color.GRAY);
        t_inv_id.setText("Inventory ID \nto change");

        JTextArea t_inv_name_num = new JTextArea();
        t_inv_name_num.setLineWrap(true);
        t_inv_name_num.setSize(100, 50);
        t_inv_name_num.setForeground(Color.GRAY);
        t_inv_name_num.setText("Type 'Item Name' \nor 'Amount' ");

        JTextArea t_inv_value = new JTextArea();
        t_inv_value.setLineWrap(true);
        t_inv_value.setSize(100, 50);
        t_inv_value.setForeground(Color.GRAY);
        t_inv_value.setText("Change current \nvalue to:");

        // add textarea to right side of inventory
        p_inv_edit.add(t_inv_id);
        p_inv_edit.add(t_inv_name_num);
        p_inv_edit.add(t_inv_value);

        // This code creates a button, we the button is pressed, whatever is on the text
        // field comes here (to this file)
        JButton b_inv_id = new JButton("Modify Data");

        // Adds buttons to left side of menu
        p_inv_edit.add(b_inv_id);

        b_inv_id.addActionListener(e -> {
            // Get the contents of the JTextArea component.
            String s_inv_id = t_inv_id.getText();
            String s_inv_name_num = t_inv_name_num.getText();
            String s_inv_value = t_inv_value.getText();
            // restore to default
            t_inv_id.setText("");
            t_inv_name_num.setText("");
            t_inv_value.setText("");

            //Update values in table

            for(int i = 0; i < inventory_data.length;++i) {
               
                String value_at = t_inventory.getValueAt(i, 0).toString();
                 if(value_at.equals(s_inv_id)) { 
                     
                     if(s_inv_name_num.equals("Item Name")) {
                         t_inventory.setValueAt(s_inv_value, i, 1);
                         break;
                     }
                     else if(s_inv_name_num.equals("Item Type"))
                     {
                        t_inventory.setValueAt(s_inv_value, i, 2);
                         break;
                     }
                     else {
                         t_inventory.setValueAt(s_inv_value, i, 3);
                         break;
                     }
                     
                 }
             } 

             Connection conns3 = null;
             try {
                 Class.forName("org.postgresql.Driver");
                 conns3 = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                         "csce315910_14user", "drowssap14");
             } catch (Exception c) {
                 c.printStackTrace();
                 System.err.println(c.getClass().getName() + ": " + c.getMessage());
                 System.exit(0);
             }
             JOptionPane.showMessageDialog(null, "Opened database successfully");
            
             try{
             // create a statement object
             //Statement stmt2 = conns.createStatement();
             String sqlStatement7;
             String sqlStatement8;
             
             // create an SQL statement - This is the right command. I am commenting it
             //because its actually going to change the database
             if(s_inv_name_num.equals("Item Name")) {
                Statement stmt7 = conns3.createStatement();
                sqlStatement7 = "UPDATE inventory SET item_name = '"+ s_inv_value
                + "' WHERE inventory_id = " + Integer.parseInt(s_inv_id) ;
                stmt7.executeUpdate(sqlStatement7);
             }
             else {
                Statement stmt8 = conns3.createStatement();
                sqlStatement8 = "UPDATE inventory SET amount_available = "+ Integer.parseInt(s_inv_value)
                + " WHERE inventory_id = " + Integer.parseInt(s_inv_id) ;
                stmt8.executeUpdate(sqlStatement8);
             }
            
             
             
             
             } catch (Exception c){
             JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
             }

             try {
                conns3.close();
                JOptionPane.showMessageDialog(null, "Connection Closed.");
            } catch (Exception c) {
                JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
            }

        });

        // create fifth tab with w/ no icon - create panel

        JPanel mod_menu_items = new JPanel();
        JLabel tab5_label = new JLabel("Menus");
        mod_menu_items.add(tab5_label, BorderLayout.NORTH);
        JPanel mod_menu_details = new JPanel();
        JSplitPane mod_menu_split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, mod_menu_items, mod_menu_details);

        tabs.addTab("Modify Menu", mod_menu_split);

        // fifth tab- creating split tabs

        // JSplitPane mod_menu_split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
        // mod_menu_items,mod_menu_details);

        mod_menu_split.setDividerLocation(800);
        mod_menu_details.setMinimumSize(min_size2);
        mod_menu_items.setMinimumSize(min_size2);

        // Add table
        // String[][] testing = ;
        // menu_content.copyInto(testing);
        JTable table = new JTable(menu_data, menu_columns);
        mod_menu_items.add(new JScrollPane(table));
        table.setEnabled(false);

        // Add tab navigator to manager frame
        manager_frame.add(tabs);

        manager_frame.setLocationRelativeTo(null);
        manager_frame.setVisible(true);

        // Add areatext and specify size
        JTextArea t_menu_id = new JTextArea();
        t_menu_id.setLineWrap(true);
        t_menu_id.setSize(100, 50);
        

        JTextArea t_menu_np = new JTextArea();
        t_menu_np.setLineWrap(true);
        t_menu_np.setSize(100, 50);

        JTextArea t_menu_value = new JTextArea();
        t_menu_value.setLineWrap(true);
        t_menu_value.setSize(100, 50);


        // add textarea to right side of menu
        mod_menu_details.add(t_menu_id);
        mod_menu_details.add(t_menu_np);
        mod_menu_details.add(t_menu_value);

        // This code creates a button, we the button is pressed, whatever is on the text
        // field comes here (to this file)
        JButton b_menu_id = new JButton("Modify Data");
        // JButton b_menu_np = new JButton("Change Menu Name or Price? Type 'Menu Name' or 'Price' ");
        // JButton b_menu_value = new JButton("Change current value to?");

        // Adds buttons to left side of menu
        mod_menu_details.add(b_menu_id);
        // mod_menu_details.add(b_menu_np);
        // mod_menu_details.add(b_menu_value);
        b_menu_id.addActionListener(e -> {
            // Get the contents of the JTextArea component.
            String s_menu_id = t_menu_id.getText();
            String s_menu_np = t_menu_np.getText();
            String s_menu_value = t_menu_value.getText();

            // restore to default
            t_menu_id.setText("");
            t_menu_np.setText("");
            t_menu_value.setText("");

            //Update values in table
            //table.setValueAt(s_menu_id, 0, 0);
            for(int i = 0; i < menu_data.length;++i) {
               
                String value_at = table.getValueAt(i, 0).toString();
                //System.out.println(dummy + "--" + s_menu_id);
                //System.out.println(dummy.equals(s_menu_id));
 
                 if(value_at.equals(s_menu_id)) { // this line is not true when its supposed to. Its actually never true. it never goes into this if statement
                     
                     if(s_menu_np.equals("Menu Name")) {
                        // menu_data[i][1] = s_menu_value;
                         table.setValueAt(s_menu_value, i, 1);
                         break;
                     }
                     else {
                         table.setValueAt(s_menu_value, i, 2);
                         break;
                     }
                     
                 }
             }
             Connection conns = null;
             try {
                 Class.forName("org.postgresql.Driver");
                 conns = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                         "csce315910_14user", "drowssap14");
             } catch (Exception a) {
                 a.printStackTrace();
                 System.err.println(a.getClass().getName() + ": " + a.getMessage());
                 System.exit(0);
             }
             JOptionPane.showMessageDialog(null, "Opened database successfully");
            
             try{
             // create a statement object
             //Statement stmt2 = conns.createStatement();
             String sqlStatement2;
             String sqlStatement3;
             
             // create an SQL statement - This is the right command. I am commenting it
             //because its actually going to change the database
             if(s_menu_np.equals("Price")) {
                Statement stmt2 = conns.createStatement();
                sqlStatement2 = "UPDATE menu SET price = "+ Float.parseFloat(s_menu_value)
                + " WHERE menu_id = " + Integer.parseInt(s_menu_id) ;
                stmt2.executeUpdate(sqlStatement2);
             }
             else {
                Statement stmt3 = conns.createStatement();
                sqlStatement3 = "UPDATE menu SET menu_name = '"+ s_menu_value
                + "' WHERE menu_id = " + Integer.parseInt(s_menu_id) ;
                stmt3.executeUpdate(sqlStatement3);
             }
            
             /*String sqlStatement2 = "UPDATE menu SET "+ s_menu_np + " = " + s_menu_value
             + " WHERE menu_id = " + s_menu_id ;*/
             
             // send statement to DBMS
             
             
             } catch (Exception a){
             JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
             }

             try {
                conns.close();
                JOptionPane.showMessageDialog(null, "Connection Closed.");
            } catch (Exception a) {
                JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
            }
             

            // prints what the user input, check your terminal
            // System.out.println("contents = " + contents);

            // this code changes the values in the table
            // table.setValueAt(contents, 0, 0);

        });


        // Start work on second button (add rows)
        JTextArea t_add_id = new JTextArea();
        t_add_id.setLineWrap(true);
        t_add_id.setSize(100, 50);

        JTextArea t_add_name = new JTextArea();
        t_add_name.setLineWrap(true);
        t_add_name.setSize(100, 50);

        JTextArea t_add_price = new JTextArea();
        t_add_price.setLineWrap(true);
        t_add_price.setSize(100, 50);

        //Create new button
        JButton b_add_row = new JButton("Add entry");

        //Add to left side of menu
        mod_menu_details.add(t_add_id);
        mod_menu_details.add(t_add_name);
        mod_menu_details.add(t_add_price);
        mod_menu_details.add(b_add_row);

        b_add_row.addActionListener(e -> {
            // Get the contents of the JTextArea component.
            String s_menu_id = t_add_id.getText();
            String s_menu_np = t_add_name.getText();
            String s_menu_value = t_add_price.getText();

            // restore to default
            t_add_id.setText("");
            t_add_name.setText("");
            t_add_price.setText("");

            Connection conns2 = null;
             try {
                 Class.forName("org.postgresql.Driver");
                 conns2 = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                         "csce315910_14user", "drowssap14");
             } catch (Exception b) {
                 b.printStackTrace();
                 System.err.println(b.getClass().getName() + ": " + b.getMessage());
                 System.exit(0);
             }
             JOptionPane.showMessageDialog(null, "Opened database successfully");

             try{
                // create a statement object
                
                String sqlStatement5;
                
                Statement stmt5 = conns2.createStatement();
                sqlStatement5 = "INSERT INTO menu (menu_id, menu_name, price) VALUES (" + Integer.parseInt(s_menu_id) + ", '" + s_menu_np + "', " + Float.parseFloat(s_menu_value) + ")" ;
                stmt5.executeUpdate(sqlStatement5);

            } catch (Exception a){
                JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
                }

                try {
                    conns2.close();
                    JOptionPane.showMessageDialog(null, "Connection Closed.");
                } catch (Exception b) {
                    JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                }

                
                
                // create an SQL statement - This is the right command. I am commenting it
                //because its actually going to change the database
                
                

                

            //TableModel model = table.getModel();
            //String[] addrow = {s_menu_id,s_menu_np,s_menu_value};
            //table.insertRow()
            //menu_data[][]
            /*
            String[][] newtable = new String[menu_data.length+1][3];
            for(int i =0 ; i < menu_data.length;++i) {
                newtable[i] = menu_data[i];
            }
           
            newtable[menu_data.length][0] = s_menu_id;
            newtable[menu_data.length][1] = s_menu_np;
            newtable[menu_data.length][2] = s_menu_value;

            
            
            
            JTable dummy = new JTable(newtable, menu_columns);
            table.clearSelection();// = new JTable(newtable,menu_columns);
            //mod_menu_items.add(dummy);
            mod_menu_items.revalidate();
            mod_menu_items.repaint();


            //model.(new Object[]{s_menu_id, s_menu_np, s_menu_value});*/
        });
        


        


        /*
         * // create main Manager GUI frame
         * f = new JFrame("Manager GUI");
         * 
         * // create a object
         * managerGUI s = new managerGUI();
         * 
         * // create a panel
         * JPanel p = new JPanel();
         * 
         * // create a "Close" button to close the window
         * JButton b = new JButton("Close");
         * 
         * // add actionlistener to button
         * b.addActionListener(s);
         * 
         * // create a JTextArea to display text in
         * JTextArea menu_items = new JTextArea(name);
         * menu_items.setEditable(false);
         * 
         * // display menu items found by query in JTextArea
         * p.add(menu_items);
         * 
         * // add button to panel
         * p.add(b);
         * 
         * // add panel to frame
         * f.add(p);
         * 
         * // set the size of frame
         * f.setSize(400, 400);
         * 
         * // set the location of the frame to the center of the screen
         * f.setLocationRelativeTo(null);
         * 
         * f.show();
         */

        // closing the connection
        try {
            conn.close();
            JOptionPane.showMessageDialog(null, "Connection Closed.");
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
        }
    }

    // if button is pressed
    public void actionPerformed(ActionEvent e) {
        String s = e.getActionCommand();
        if (s.equals("Close")) {
            manager_frame.dispose();
        }
    }
}
