import java.sql.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

public class serverGUI extends JFrame {
    static JFrame f;

    public static void main(String[] args) {
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
        JOptionPane.showMessageDialog(null,"Opened database successfully");

        String name = "";
        try {
            // For view menu pop up
            Statement stmt = conn.createStatement();
            String sqlStatement = "SELECT * FROM menu";
            ResultSet result = stmt.executeQuery(sqlStatement);
            while (result.next()) {
                name += result.getString("menu_id") + " - " + result.getString("menu_name") + "\n";
            }
            
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null,"Error accessing Database.");
        }

        /* Frame declarations */

            // Main serverGUI frame
            JFrame f_serverGUI = new JFrame("ServerGUI");
            f_serverGUI.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f_serverGUI.setSize(1200, 800);

            // View Menu frame
            JFrame f_menu_view = new JFrame("Menu View");
            f_menu_view.setSize(600, 400);

            // Select from Menu frame
            JFrame f_menu_select = new JFrame("Menu Select");
            f_menu_select.setSize(600, 400);

        /* Main serverGUI frame implementation */

            /* Order Display panel (left) */

                /* Text & Labels */

                    // Orders label
                    JLabel l_order_label = new JLabel("Orders");
                    
                    // Order Information Display (scrolling text box)
                    String s_curr_orders = updateOrders();
                    JTextArea t_orders_text = new JTextArea(s_curr_orders);
                    t_orders_text.setLineWrap(true);
                    t_orders_text.setWrapStyleWord(true);
                    JScrollPane p_curr_orders = new JScrollPane(t_orders_text);

                /* Panels & Organization */

                    // Label panel
                    JPanel p_order_label = new JPanel();
                    p_order_label.add(l_order_label);

                    // Information & Label panel
                    JPanel p_order_display = new JPanel(new BorderLayout());
                    p_order_display.add(p_order_label, BorderLayout.NORTH);
                    p_order_display.add(p_curr_orders, BorderLayout.CENTER);

            /* New Order panel (top-right) */

                /* Text & Labels */

                    // Order ID
                    JLabel l_new_id = new JLabel("Order ID:");

                    // Customer Name
                    JLabel l_customer_name = new JLabel("Customer Name:");
                    JTextField t_customer_name = new JTextField(40);

                    // Order Contents
                    JLabel l_order_items = new JLabel("Order Contents:");
                    JTextArea t_order_items = new JTextArea(2, 40);
                    t_order_items.setEditable(false);
                    t_order_items.setLineWrap(true);
                    t_order_items.setWrapStyleWord(true);
                    JScrollPane p_order_items_scroll = new JScrollPane(t_order_items);

                    // Notes
                    JLabel l_notes = new JLabel("Notes:");
                    JTextArea t_notes = new JTextArea(4, 40);
                    t_notes.setLineWrap(true);
                    t_notes.setWrapStyleWord(true);
                    JScrollPane p_notes_scroll = new JScrollPane(t_notes);

                /* Buttons */

                    // Create New Order
                    JButton b_order_create = new JButton("Create Order");
                    b_order_create.addActionListener(e->{

                        // Pull customer info from user input
                        String customer_name = t_customer_name.getText();
                        String order_notes = t_notes.getText();

                        // Pull and parse order contents from user input
                        String order_contents= t_order_items.getText();
                        Scanner scanner = new Scanner(order_contents);
                        List<String> words= new ArrayList<>();
                        while(scanner.hasNextLine()){
                            Scanner line= new Scanner(scanner.nextLine());
                            while (line.hasNext()){
                                words.add(line.next());
                            }
                            line.close();
                        }
                        scanner.close();

                        // Open a new connection to the database that only activates when button is pressed
                        Connection conn2 = null;
                        try {
                            Class.forName("org.postgresql.Driver");
                            conn2 = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                            "csce315910_14user", "drowssap14");
                        } catch (Exception e2) {
                            e2.printStackTrace();
                            System.err.println(e2.getClass().getName() + ": " + e2.getMessage());
                            System.exit(0);
                        }
                        // JOptionPane.showMessageDialog(null,"Opened database successfully");

                        // Insert new order data into database
                        try {
                            // Retrieve most recent customer ID
                            String s_temp_customer = "";
                            Statement stat_customer_id = conn2.createStatement();
                            String s_customer_id = "SELECT * FROM customer ORDER BY customer_id DESC LIMIT 1";
                            ResultSet res_customer_id = stat_customer_id.executeQuery(s_customer_id);
                            while(res_customer_id.next()){
                                s_temp_customer += res_customer_id.getString("customer_id");
                            }
                            int latest_customer_id = Integer.parseInt(s_temp_customer);
                        
                            // Enters customer information into the database
                            Statement stat_customer_info = conn2.createStatement();
                            String s_customer_info = "INSERT INTO customer(customer_id, customer_name, complete, notes) VALUES("+ (latest_customer_id+1) +", '"+customer_name+"', "+ 0+", '"+ order_notes+"')";
                            stat_customer_info.executeUpdate(s_customer_info);
                        
                            // Retrieve most recent order ID
                            String s_temp_order = "";
                            Statement stat_order_id = conn2.createStatement();
                            String s_order_id = "SELECT * FROM orders ORDER BY order_id DESC LIMIT 1";
                            ResultSet res_order_id = stat_order_id.executeQuery(s_order_id);
                            while(res_order_id.next()){
                                s_temp_order += res_order_id.getString("order_id");
                            }
                            int latest_order_id = Integer.parseInt(s_temp_order);

                            // Enters order information into the database
                            Statement stat_order_info;
                            String s_order_info;
                            for(int i=0; i<words.size(); i+=2){
                                stat_order_info= conn2.createStatement();
                                s_order_info = "INSERT INTO orders(order_id, menu_id, quantity, customer_id) VALUES("+ (latest_order_id+1) +", "+Integer.parseInt(words.get(i))+", "+ Integer.parseInt(words.get(i+1))+", "+ (latest_customer_id+1) +")";
                                stat_order_info.executeUpdate(s_order_info);
                                latest_order_id++;
                            }

                            // TODO: function which re-displays the order table *******************

                        } catch (Exception e2) {
                            JOptionPane.showMessageDialog(null,"Error importing data.");
                        }

                        // Closes button connection to database
                        try {
                            conn2.close();
                            // JOptionPane.showMessageDialog(null,"Connection Closed.");
                        } catch(Exception e2) {
                            JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
                        }

                        // Clear old information from text fields
                        t_customer_name.setText("");
                        t_order_items.setText("");
                        t_notes.setText("");

                        // Update orders table
                        t_orders_text.setText(updateOrders());
                    });

                    // Select from Menu
                    JButton b_menu_select = new JButton("Select from Menu");
                    b_menu_select.addActionListener(e->{
                        f_menu_select.setLocationRelativeTo(null);
                        f_menu_select.setVisible(true);
                    });

                    // Reset Order
                    JButton b_menu_clear = new JButton("Reset Order");
                    b_menu_clear.addActionListener(e->{
                        t_order_items.setText("");
                    });

                /* Panels & Organization */

                    // Customer Name panel
                    JPanel p_customer_name = new JPanel(new BorderLayout());
                    p_customer_name.add(l_customer_name, BorderLayout.NORTH);
                    p_customer_name.add(t_customer_name, BorderLayout.CENTER);

                    // Order Contents panel
                    JPanel p_order_items = new JPanel(new BorderLayout());
                    p_order_items.add(l_order_items, BorderLayout.NORTH);
                    p_order_items.add(p_order_items_scroll, BorderLayout.CENTER);
                    p_order_items.add(b_menu_clear, BorderLayout.EAST);

                    // Notes panel
                    JPanel p_notes = new JPanel(new BorderLayout());
                    p_notes.add(l_notes, BorderLayout.NORTH);
                    p_notes.add(p_notes_scroll, BorderLayout.CENTER);

                    // Buttons panel
                    JPanel p_order_create_buttons = new JPanel(new GridLayout(1,2,6,6));
                    p_order_create_buttons.add(b_order_create);
                    p_order_create_buttons.add(b_menu_select);

                    // Organization panels
                    JPanel p_id_name_shrink = new JPanel(new GridLayout(2,0,6,6));
                    p_id_name_shrink.add(l_new_id);
                    p_id_name_shrink.add(p_customer_name);
                    JPanel p_new_order = new JPanel(new GridLayout(4,0,6,6));
                    p_new_order.add(p_id_name_shrink);
                    p_new_order.add(p_order_items);
                    p_new_order.add(p_notes);
                    p_new_order.add(p_order_create_buttons);
            
            /* Controls (bottom-right) */

                /* Text & Labels */

                    // Current Time
                    JTextArea t_curr_time = new JTextArea("[Current Time]", 1, 15);
                    t_curr_time.setEditable(false);

                    // Current Location
                    JTextArea t_curr_location = new JTextArea("[Current Location]",1,15);
                    t_curr_location.setEditable(false);

                /* Buttons */

                    // Mark Order as Complete
                    JButton b_comp_order = new JButton("Complete Order");

                    // Cancel Order
                    JButton b_cancel_order = new JButton("Cancel Order");

                    // View Menu
                    JButton b_menu_view = new JButton("View Menu");
                    b_menu_view.addActionListener(e->{
                        f_menu_view.setLocationRelativeTo(null);
                        f_menu_view.setVisible(true);
                    });

                    // Change Location
                    JButton b_location_change = new JButton("Change Location");

                /* Panels & Organization */
                    
                    // Options panel (3x2 grid)
                    JPanel p_controls = new JPanel(new GridLayout(3,2,6,6));
                    p_controls.add(t_curr_time);
                    p_controls.add(b_menu_view);
                    p_controls.add(t_curr_location);
                    p_controls.add(b_location_change);
                    p_controls.add(b_comp_order);
                    p_controls.add(b_cancel_order);

            /* Split Panes */
            
                // Top-Bottom split on right side
                JSplitPane tb_split = new JSplitPane(JSplitPane.VERTICAL_SPLIT, p_new_order, p_controls);
                tb_split.setDividerLocation(400);
                Dimension min_size2 = new Dimension(590, 390);
                p_new_order.setMinimumSize(min_size2);
                p_controls.setMinimumSize(min_size2);

                // Left-Right split
                JSplitPane lr_split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, p_order_display, tb_split);
                lr_split.setDividerLocation(600);
                Dimension min_size = new Dimension(590, 790);
                p_order_display.setMinimumSize(min_size);
                tb_split.setMinimumSize(min_size);

            // Adding objects to serverGUI frame
            f_serverGUI.getContentPane().add(lr_split,BorderLayout.CENTER);
            f_serverGUI.setLocationRelativeTo(null);
            f_serverGUI.setVisible(true);

        /* View Menu frame implementation */

            /* Text & Labels */

                // Menu Information (scrolling text box)
                JTextArea t_menu_view = new JTextArea(name);
                t_menu_view.setLineWrap(true);
                t_menu_view.setWrapStyleWord(true);
                t_menu_view.setEditable(false);
                JScrollPane p_menu_view_scroll = new JScrollPane(t_menu_view);

            /* Buttons */

                // Cancel button
                JButton b_menu_view_cancel = new JButton("Cancel");
                b_menu_view_cancel.addActionListener(e->{
                    f_menu_view.dispose();
                });

            /* Panels & Organization */

                // Cancel Button panel
                JPanel p_menu_view_options = new JPanel();
                p_menu_view_options.add(b_menu_view_cancel);

                // Menu Information & Options panel
                JPanel p_view_menu = new JPanel(new BorderLayout());
                p_view_menu.add(p_menu_view_scroll, BorderLayout.CENTER);
                p_view_menu.add(p_menu_view_options, BorderLayout.SOUTH);

                // Add main panel to frame
                f_menu_view.add(p_view_menu);

        /* Select from Menu frame implementation */
            
            /* Text and Labels */

                // Menu Information (scrolling text box)
                JTextArea t_menu_select = new JTextArea(name);
                t_menu_select.setLineWrap(true);
                t_menu_select.setWrapStyleWord(true);
                t_menu_select.setEditable(false);
                JScrollPane p_menu_select_scroll = new JScrollPane(t_menu_select);

                // Menu ID
                JLabel l_menu_id = new JLabel("Menu ID:");
                JTextField t_menu_id = new JTextField(10);

                // Menu item Quantity
                JLabel l_menu_quantity = new JLabel("Quantity:");
                JTextField t_menu_quantity = new JTextField(10);

            /* Buttons */

                // Confirmation button
                JButton b_menu_confirm = new JButton("Add to Order");
                b_menu_confirm.addActionListener(e->{
                    // Update display in Order Contents text area
                    String new_menu_id = t_menu_id.getText();
                    String new_quantity = t_menu_quantity.getText();
                    t_order_items.append(new_menu_id + " " + new_quantity + "\n");
                    // Reset text fields and close panel
                    t_menu_id.setText("");
                    t_menu_quantity.setText("");
                    f_menu_select.dispose();
                });

                // Cancel button
                JButton b_menu_select_cancel = new JButton("Cancel");
                b_menu_select_cancel.addActionListener(e->{
                    // Reset text fields and close panel
                    t_menu_id.setText("");
                    t_menu_quantity.setText("");
                    f_menu_select.dispose();
                });

            /* Panels and Organization */

                // Menu ID & Quantity panel (with buttons)
                JPanel p_menu_select_options = new JPanel();
                p_menu_select_options.add(l_menu_id);
                p_menu_select_options.add(t_menu_id);
                p_menu_select_options.add(l_menu_quantity);
                p_menu_select_options.add(t_menu_quantity);
                p_menu_select_options.add(b_menu_confirm);
                p_menu_select_options.add(b_menu_select_cancel);

                // Menu Information & Options panel
                JPanel p_menu_select = new JPanel(new BorderLayout());
                p_menu_select.add(p_menu_select_scroll, BorderLayout.CENTER);
                p_menu_select.add(p_menu_select_options, BorderLayout.SOUTH);

                // Add main panel to frame
                f_menu_select.add(p_menu_select);
        
        // closing the connection
        try {
            conn.close();
            JOptionPane.showMessageDialog(null,"Connection Closed.");
        } catch(Exception e) {
            JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
        }
    }

    static String updateOrders() {
        // TODO:
        // do customer query (customers with 0 for completed)
        // parse information
        // do order queries (using customer id)
        // parse information
        // organize information and add to string s_curr_orders (after starting it at "")
        // ^^ all of this ^^ should be a separate function, which will be called when:
            // creating an order (here)
            // completing an order
            // canceling an order

        String s_return = "";

        // Opening connection to database
        Connection update_conn = null;
        try {
            Class.forName("org.postgresql.Driver");
            update_conn = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
            "csce315910_14user", "drowssap14");
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }
        // JOptionPane.showMessageDialog(null,"Opened database successfully");

        String customer_list = "";
        try {
            // For view menu pop up
            Statement stat_update_customer = update_conn.createStatement();
            String s_update_customer = "SELECT * FROM customer WHERE complete=0";
            ResultSet res_update_customer = stat_update_customer.executeQuery(s_update_customer);
            while (res_update_customer.next()) {
                customer_list += res_update_customer.getString("customer_id") + " - " + res_update_customer.getString("customer_name") + " - " + res_update_customer.getString("notes") + "\n";
                customer_list += "===============================================" + "\n";
            }

            s_return = customer_list;

            //String s_update_order = "SELECT * FROM orders WHERE customer_id=" + [customer id]];

            // Retrieve most recent customer ID - TODO: move this to function for refreshing orders table *******************
            /*
            String s_last_id = "";
            Statement stmt_last_id = conn.createStatement();
            String s_sql_last_id = "SELECT * FROM customer ORDER BY customer_id DESC LIMIT 1";
            ResultSet res_last_id = stmt_last_id.executeQuery(s_sql_last_id);
            while(res_last_id.next()){
                s_last_id += res_last_id.getString("customer_id");
            }
            int int_last_id = Integer.parseInt(s_last_id);
            // TODO: make sure it actually updates label
            */
            
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null,"Error accessing Database.");
        }

        // Closing the connection
        try {
            update_conn.close();
            // JOptionPane.showMessageDialog(null,"Connection Closed.");
        } catch(Exception e) {
            JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
        }

        return s_return;
    }
}
