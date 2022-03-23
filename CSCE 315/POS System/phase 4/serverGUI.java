import java.sql.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;
import java.time.format.DateTimeFormatter;  
import java.time.LocalDateTime;    

public class serverGUI extends JFrame {
    static JFrame f;

    public static void main(String[] args) {

        // Building the initial connection with team database credentials
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
                    t_orders_text.setEditable(false);
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


            /* Declaring time display variable from bottom left panel early for scope reasons */

                // Current Time
                JTextArea t_curr_time = new JTextArea(updateTime());
                t_curr_time.setEditable(false);
                Font font = new Font("Segoe Script", Font.BOLD, 20);
                t_curr_time.setFont(font);

            /* New Order panel (top-right) */

                /* Text & Labels */

                    // Order ID
                    JLabel l_new_id = new JLabel("Order ID: " + updateOrderID());

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
                            
                            // Retrieve each order's price information from database menu and calculate total price
                            String curr_order_id = "";
                            int curr_order_quantity = 0;
                            double price_total = 0;
                            Statement stat_order_price;
                            String s_order_price;
                            for (int i = 0; i < words.size(); i += 2) {
                                // Store each order's ID and quantity
                                curr_order_id = words.get(i);
                                curr_order_quantity = Integer.parseInt(words.get(i + 1));

                                // Retrieve each order's price from database menu
                                Statement stat_menu_price = conn2.createStatement();
                                String s_menu_price = "SELECT * FROM menu WHERE menu_id=" + curr_order_id;
                                ResultSet res_menu_price = stat_menu_price.executeQuery(s_menu_price);
                                
                                // Add the order's price multiplied by quantity to the total price
                                while(res_menu_price.next()){
                                   price_total += Double.parseDouble(res_menu_price.getString("price")) * curr_order_quantity;
                                }
                            }

                            // Determine time of order
                            Timestamp order_time = Timestamp.valueOf(LocalDateTime.now());
                        
                            // Enters customer information into the database
                            Statement stat_customer_info = conn2.createStatement();
                            String s_customer_info = "INSERT INTO customer(customer_id, customer_name, complete, notes, order_cost, time) VALUES(" + (latest_customer_id + 1) + ", '" + customer_name + "', " + 0 + ", '" + order_notes + "', '" + price_total + "', '" + order_time + "')";
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

                        // Update orders table, next order ID, and current time
                        l_new_id.setText("Order ID: " + updateOrderID());
                        t_orders_text.setText(updateOrders());
                        t_curr_time.setText(updateTime());
                    });

                    // Select from Menu
                    JButton b_menu_select = new JButton("Select from Menu");
                    b_menu_select.addActionListener(e->{
                        f_menu_select.setLocationRelativeTo(null);
                        f_menu_select.setVisible(true);

                        // Update time
                        t_curr_time.setText(updateTime());
                    });

                    // Reset Order
                    JButton b_menu_clear = new JButton("Reset Order");
                    b_menu_clear.addActionListener(e->{
                        t_order_items.setText("");

                        // Update time
                        t_curr_time.setText(updateTime());
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

                    // Order ID selection
                    JLabel l_order_id_select = new JLabel("Order ID:");
                    JTextField t_order_id_select = new JTextField(15);

                /* Buttons */

                    // Mark Order as Complete
                    JButton b_comp_order = new JButton("Complete Order");
                    b_comp_order.addActionListener(e->{
                        // Get customer ID from order ID text field
                        int comp_customer_id = Integer.parseInt(t_order_id_select.getText());

                        // Start a connection to the database
                        Connection conn_comp = null;
                        try {
                            Class.forName("org.postgresql.Driver");
                            conn_comp = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                            "csce315910_14user", "drowssap14");
                        } catch (Exception e2) {
                            e2.printStackTrace();
                            System.err.println(e2.getClass().getName() + ": " + e2.getMessage());
                            System.exit(0);
                        }

                        try {
                            // Connect to database orders table based on customer ID
                            Statement stmt_comp_order = conn_comp.createStatement();
                            String s_comp_order = "SELECT * FROM orders WHERE customer_id=" + comp_customer_id;
                            ResultSet res_comp_order = stmt_comp_order.executeQuery(s_comp_order);

                            // Parse through each order
                            while(res_comp_order.next()){
                                // Get menu ID and quantity from order table
                                int comp_menu_id = Integer.parseInt(res_comp_order.getString("menu_id"));
                                int comp_order_quantity = Integer.parseInt(res_comp_order.getString("quantity"));

                                // Connect to database recipe table based on menu ID per order
                                Statement stmt_comp_recipe = conn_comp.createStatement();
                                String s_comp_recipe = "SELECT * FROM recipe WHERE menu_id=" + comp_menu_id;
                                ResultSet res_comp_recipe = stmt_comp_recipe.executeQuery(s_comp_recipe);

                                // Parse through each recipe
                                while(res_comp_recipe.next()) {
                                    // Get inventory ID and quantity from recipe table
                                    int comp_inv_id = Integer.parseInt(res_comp_recipe.getString("inventory_id"));
                                    double comp_inv_quantity = Double.parseDouble(res_comp_recipe.getString("quantity"));
                                    double comp_inv_amount = 0;

                                    // Connect to database inventory table based on inventory ID per recipe
                                    Statement stmt_comp_inv = conn_comp.createStatement();
                                    String s_comp_inv = "SELECT * FROM inventory WHERE inventory_id=" + comp_inv_id;
                                    ResultSet res_comp_inv = stmt_comp_inv.executeQuery(s_comp_inv);

                                    // Parse through inventory listing
                                    while(res_comp_inv.next()) {
                                        // Get amount available from inventory table
                                        comp_inv_amount = Double.parseDouble(res_comp_inv.getString("amount_available"));
                                    }

                                    // Calculate new inventory amount based on recipe and order quantities
                                    comp_inv_amount = comp_inv_amount - (comp_inv_quantity * comp_order_quantity);

                                    // Subtract used amount from inventory item used
                                    Statement stat_comp_inv_subtract = conn_comp.createStatement();
                                    String s_comp_inv_subtract = "UPDATE inventory SET amount_available=" + comp_inv_amount + " WHERE inventory_id=" + comp_inv_id;
                                    stat_comp_inv_subtract.executeUpdate(s_comp_inv_subtract);
                                }

                                // Connect to database customer table based on customer ID
                                Statement stmt_comp_customer = conn_comp.createStatement();
                                String s_comp_customer = "SELECT * FROM customer WHERE customer_id=" + comp_customer_id;
                                ResultSet res_comp_customer = stmt_comp_customer.executeQuery(s_comp_customer);

                                // Parse through customer
                                String s_customer_date = "";
                                while (res_comp_customer.next()) {
                                    // Get time ordered from customer table
                                    s_customer_date = res_comp_customer.getString("time");
                                    String[] s_customer_datetime = s_customer_date.split(" ");
                                    s_customer_date = s_customer_datetime[0];
                                }

                                // Find last used trend ID
                                int latest_trend_id = 0;
                                Statement stmt_comp_trend_id = conn_comp.createStatement();
                                String s_comp_trend_id = "SELECT * FROM trends ORDER BY trend_id DESC LIMIT 1";
                                ResultSet res_comp_trend_id = stmt_comp_trend_id.executeQuery(s_comp_trend_id);
                                while (res_comp_trend_id.next()) {
                                    latest_trend_id = Integer.parseInt(res_comp_trend_id.getString("trend_id"));
                                }

                                // Connect to database trends table based on menu ID and date per order
                                Statement stmt_comp_trend_check = conn_comp.createStatement();
                                String s_comp_trend_check = "SELECT * FROM trends WHERE menu_id=" + comp_menu_id + " and trend_date='" + s_customer_date + "'";
                                ResultSet res_comp_trend_check = stmt_comp_trend_check.executeQuery(s_comp_trend_check);

                                // Parse through trend
                                boolean trend_exists = false;
                                int trend_ordered = comp_order_quantity;
                                while (res_comp_trend_check.next()) {
                                    // Check if a trend exists for that day and item; if so, take note of the existing times ordered
                                    trend_exists = true;
                                    trend_ordered += Integer.parseInt(res_comp_trend_check.getString("times_ordered"));
                                }
                                
                                // Update the trends table accordingly
                                if (trend_exists) {
                                    // If there is an existing trend, update the number of times ordered
                                    Statement stat_comp_trend_update = conn_comp.createStatement();
                                    String s_comp_trend_update = "UPDATE trends SET times_ordered=" + trend_ordered + " WHERE menu_id=" + comp_menu_id + " and trend_date= '" + s_customer_date + "'";
                                    stat_comp_trend_update.executeUpdate(s_comp_trend_update);

                                } else {
                                    // If there is not such a trend, add a new trend to the table
                                    Statement stat_comp_trend_update = conn_comp.createStatement();
                                    String s_comp_trend_update = "INSERT INTO trends(trend_id, trend_date, menu_id, times_ordered) VALUES(" + (latest_trend_id + 1) + ", '" + s_customer_date + "', " + comp_menu_id + ", " + trend_ordered + ")";
                                    stat_comp_trend_update.executeUpdate(s_comp_trend_update);
                                }
                            }
                            
                            // Mark order as completed in database
                            Statement stat_comp_customer = conn_comp.createStatement();
                            String s_comp_customer = "UPDATE customer SET complete=1 WHERE customer_id=" + comp_customer_id;
                            stat_comp_customer.executeUpdate(s_comp_customer);

                        } catch (Exception e2) {
                            JOptionPane.showMessageDialog(null,"Error accessing Database.");
                        }

                        // Close the connection
                        try {
                            conn_comp.close();
                        } catch(Exception e2) {
                            JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
                        }

                        // Clear order ID text field
                        t_order_id_select.setText("");

                        // Update orders table and current time
                        t_orders_text.setText(updateOrders());
                        t_curr_time.setText(updateTime());
                    });

                    // Cancel Order
                    JButton b_cancel_order = new JButton("Cancel Order");
                    b_cancel_order.addActionListener(e->{
                        // Get customer id from order ID text field
                        int customer_id_cancel = Integer.parseInt(t_order_id_select.getText());

                        // Start a connection to the database
                        Connection conn_cancel = null;
                        try {
                            Class.forName("org.postgresql.Driver");
                            conn_cancel = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                            "csce315910_14user", "drowssap14");
                        } catch (Exception e2) {
                            e2.printStackTrace();
                            System.err.println(e2.getClass().getName() + ": " + e2.getMessage());
                            System.exit(0);
                        }
                        
                        // Remove customer and order listings from database if not yet completed
                        try {
                            // Check if order has been completed already
                            boolean cancel_completed = false;
                            Statement stmt_cancel_complete = conn_cancel.createStatement();
                            String s_cancel_complete = "SELECT * FROM customer WHERE customer_id=" + customer_id_cancel;
                            ResultSet res_cancel_complete = stmt_cancel_complete.executeQuery(s_cancel_complete);
                            while(res_cancel_complete.next()){
                                if (Integer.parseInt(res_cancel_complete.getString("complete")) == 1) {
                                    cancel_completed = true;
                                }
                            }

                            // Only remove order if not yet completed
                            if (cancel_completed == false) {
                                // Delete the customer listing matching the customer ID from the database
                                Statement stat_cancel_customer = conn_cancel.createStatement();
                                String s_cancel_customer = "DELETE FROM customer WHERE customer_id=" + customer_id_cancel;
                                stat_cancel_customer.executeUpdate(s_cancel_customer);

                                // Delete all order listings matching the customer ID from the database
                                Statement stat_cancel_order = conn_cancel.createStatement();
                                String s_update_order = "DELETE FROM orders WHERE customer_id=" + customer_id_cancel;
                                stat_cancel_order.executeUpdate(s_update_order);
                            }

                        } catch (Exception e2) {
                            JOptionPane.showMessageDialog(null,"Error accessing Database.");
                        }

                        // Close the connection
                        try {
                            conn_cancel.close();
                        } catch(Exception e2) {
                            JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
                        }

                        // Clear order ID text field
                        t_order_id_select.setText("");

                        // Update orders table, next order ID, and current time
                        l_new_id.setText("Order ID: " + updateOrderID());
                        t_orders_text.setText(updateOrders());
                        t_curr_time.setText(updateTime());
                    });

                    // View Menu
                    JButton b_menu_view = new JButton("View Menu");
                    b_menu_view.addActionListener(e->{
                        f_menu_view.setLocationRelativeTo(null);
                        f_menu_view.setVisible(true);

                        // Update time
                        t_curr_time.setText(updateTime());
                    });

                /* Panels & Organization */
                    
                    // Top options panel (1x2 grid)
                    JPanel p_controls_top = new JPanel(new GridLayout(1, 2, 6, 6));
                    p_controls_top.add(t_curr_time);
                    p_controls_top.add(b_menu_view);

                    // Order ID select panel
                    JPanel p_controls_id = new JPanel();
                    p_controls_id.add(l_order_id_select);
                    p_controls_id.add(t_order_id_select);

                    // Order ID alignment panel
                    JPanel p_controls_id_west = new JPanel(new BorderLayout());
                    p_controls_id_west.add(p_controls_id, BorderLayout.WEST);

                    // Bottom buttons panel (1x2 grid)
                    JPanel p_controls_bottom_buttons = new JPanel(new GridLayout(1, 2, 6, 6));
                    p_controls_bottom_buttons.add(b_comp_order);
                    p_controls_bottom_buttons.add(b_cancel_order);

                    // Order ID cancel/complete panel
                    JPanel p_controls_bottom = new JPanel(new BorderLayout());
                    p_controls_bottom.add(p_controls_id_west, BorderLayout.NORTH);
                    p_controls_bottom.add(p_controls_bottom_buttons, BorderLayout.CENTER);

                    // Controls organization panel (2x1 grid)
                    JPanel p_controls = new JPanel(new GridLayout(2, 1, 6, 6));
                    p_controls.add(p_controls_top);
                    p_controls.add(p_controls_bottom);

            /* Split Panes */
            
                // Top-Bottom split on right side
                JSplitPane tb_split = new JSplitPane(JSplitPane.VERTICAL_SPLIT, p_new_order, p_controls);
                tb_split.setDividerLocation(500);
                Dimension min_size2 = new Dimension(600, 400);
                p_new_order.setMinimumSize(min_size2);
                p_controls.setMinimumSize(min_size2);

                // Left-Right split
                JSplitPane lr_split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, p_order_display, tb_split);
                lr_split.setDividerLocation(600);
                Dimension min_size = new Dimension(600, 800);
                p_order_display.setMinimumSize(min_size);
                tb_split.setMinimumSize(min_size);

            // Adding objects to serverGUI frame
            f_serverGUI.getContentPane().add(lr_split,BorderLayout.CENTER);
            f_serverGUI.setLocationRelativeTo(null);
            f_serverGUI.setVisible(true);

        /* View Menu frame implementation */

            /* Text & Labels */

                // Menu Information (scrolling text box)
                JTextArea t_menu_view = new JTextArea(updateMenu());
                t_menu_view.setLineWrap(true);
                t_menu_view.setWrapStyleWord(true);
                t_menu_view.setEditable(false);
                JScrollPane p_menu_view_scroll = new JScrollPane(t_menu_view);

            /* Buttons */

                // Cancel button
                JButton b_menu_view_cancel = new JButton("Cancel");
                b_menu_view_cancel.addActionListener(e->{
                    f_menu_view.dispose();

                    // Update time
                    t_curr_time.setText(updateTime());
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
                JTextArea t_menu_select = new JTextArea(updateMenu());
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

                    // Update time
                    t_curr_time.setText(updateTime());
                });

                // Cancel button
                JButton b_menu_select_cancel = new JButton("Cancel");
                b_menu_select_cancel.addActionListener(e->{
                    // Reset text fields and close panel
                    t_menu_id.setText("");
                    t_menu_quantity.setText("");
                    f_menu_select.dispose();

                    // Update time
                    t_curr_time.setText(updateTime());
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
        
        // Closing the initial connection
        try {
            conn.close();
            JOptionPane.showMessageDialog(null,"Connection Closed.");
        } catch(Exception e) {
            JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
        }
    }

    /* Functions */

        // Function for retrieving the menu list

        static String updateMenu() {
            // Create empty string to be returned when it contains the loaded menu
            String s_return = "";

            // Open connection to database
            Connection conn_function = null;
            try {
                Class.forName("org.postgresql.Driver");
                conn_function = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                "csce315910_14user", "drowssap14");
            } catch (Exception e) {
                e.printStackTrace();
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
                System.exit(0);
            }

            try {
                // Connect to database menu table to retrieve menu ID and name listings
                Statement stmt_menu = conn_function.createStatement();
                String s_menu = "SELECT * FROM menu ORDER BY menu_id";
                ResultSet res_menu = stmt_menu.executeQuery(s_menu);
                while (res_menu.next()) {
                    s_return += res_menu.getString("menu_id") + " - " + res_menu.getString("menu_name") + "\n";
                }
                
            } catch (Exception e) {
                JOptionPane.showMessageDialog(null,"Error accessing Database.");
            }

            // Close the connection
            try {
                conn_function.close();
            } catch(Exception e) {
                JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
            }

            // Return the refreshed menu
            return s_return;
        }

        // Function for changing the time
        static String updateTime() {
            // Create empty string to be returned when it contains the current time
            String s_return= "";

            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm");  
            LocalDateTime now = LocalDateTime.now();

            s_return=dtf.format(now);

            // Return current time
            return s_return;
        }

        // Function for retrieving the next order's Order ID
        static String updateOrderID() {
            // Create empty string to be returned when it contains the new order ID
            String s_return = "";

            // Open connection to database
            Connection conn_function = null;
            try {
                Class.forName("org.postgresql.Driver");
                conn_function = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                "csce315910_14user", "drowssap14");
            } catch (Exception e) {
                e.printStackTrace();
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
                System.exit(0);
            }

            // Access information contained within database
            try {
                // Retrieve last-used order ID
                String s_last_id = "";
                Statement stmt_last_id = conn_function.createStatement();
                String s_sql_last_id = "SELECT * FROM customer ORDER BY customer_id DESC LIMIT 1";
                ResultSet res_last_id = stmt_last_id.executeQuery(s_sql_last_id);
                while(res_last_id.next()){
                    s_last_id += res_last_id.getString("customer_id");
                }
                int int_last_id = Integer.parseInt(s_last_id);

                // Update return string to contain order ID value
                s_return = String.valueOf(int_last_id + 1);

            } catch (Exception e) {
                JOptionPane.showMessageDialog(null,"Error accessing Database.");
            }

            // Close the connection
            try {
                conn_function.close();
            } catch(Exception e) {
                JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
            }

            // Return next order's Order ID
            return s_return;
        }

        // Function for refreshing information displayed in the order list
        static String updateOrders() {
            // Create empty string to be returned when it contains the order list
            String s_return = "";

            // Open connection to database
            Connection conn_function = null;
            try {
                Class.forName("org.postgresql.Driver");
                conn_function = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                "csce315910_14user", "drowssap14");
            } catch (Exception e) {
                e.printStackTrace();
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
                System.exit(0);
            }

            try {
                // Access database customer information
                Statement stat_update_customer = conn_function.createStatement();
                String s_update_customer = "SELECT * FROM customer WHERE complete=0";
                ResultSet res_update_customer = stat_update_customer.executeQuery(s_update_customer);

                // Create variables for use in customer parsing
                String s_customer_id_display = "";
                String s_customer_name = "";
                String s_customer_price = "";
                String s_customer_notes = "";
                String s_customer_time = "";

                // Parse through customer information
                while (res_update_customer.next()) {
                    // Parse customer ID, name, total price, notes, and order time into variables
                    s_customer_id_display = res_update_customer.getString("customer_id");
                    s_customer_name = res_update_customer.getString("customer_name");
                    s_customer_price = res_update_customer.getString("order_cost");
                    s_customer_notes = res_update_customer.getString("notes");
                    s_customer_time = res_update_customer.getString("time");
                    String[] s_customer_datetime = s_customer_time.split(" ");
                    s_customer_time = s_customer_datetime[1];

                    // Add each customer's id, name, and time ordered to the return string
                    s_return += "Order ID: " + s_customer_id_display + "\n";
                    s_return += "Customer Name: " + s_customer_name + "\n";
                    s_return += "Time Ordered: " + s_customer_time + "\n";
                    s_return += "Order Contents:" + "\n";

                    // Access database orders information
                    Statement stat_update_orders = conn_function.createStatement();
                    String s_update_orders = "SELECT * FROM orders WHERE customer_id=" + Integer.parseInt(s_customer_id_display);
                    ResultSet res_update_orders = stat_update_orders.executeQuery(s_update_orders);

                    // Create variables for use in order parsing
                    String s_order_item = "";
                    String s_order_name = "";
                    String s_order_quantity = "";

                    // Parse through order information
                    while (res_update_orders.next()) {
                        // Parse order item id, quantity, and price into variables
                        s_order_item = res_update_orders.getString("menu_id");
                        s_order_quantity = res_update_orders.getString("quantity");

                        // Access database menu information by item id
                        Statement stat_update_order_name = conn_function.createStatement();
                        String s_update_order_name = "SELECT * FROM menu WHERE menu_id=" + Integer.parseInt(s_order_item);
                        ResultSet res_update_order_name = stat_update_order_name.executeQuery(s_update_order_name);

                        // Find menu item name
                        while (res_update_order_name.next()) {
                            s_order_name = res_update_order_name.getString("menu_name");
                        }

                        // Add each order's information to the return string
                        s_return += "   Item " + s_order_item;
                        s_return += " (" + s_order_name + ")";
                        s_return += " x" + s_order_quantity;
                        s_return += "\n";
                    }

                    // Add each customer's total price and notes to the return string
                    s_return += "Total Price: $" + s_customer_price + "\n";
                    s_return += "Notes: " + s_customer_notes + "\n";

                    // Separate out each customer's order in the return string
                    s_return += "===============================================" + "\n";
                }
                
            } catch (Exception e) {
                JOptionPane.showMessageDialog(null,"Error accessing Database.");
            }

            // Close the connection
            try {
                conn_function.close();
            } catch(Exception e) {
                JOptionPane.showMessageDialog(null,"Connection NOT Closed.");
            }

            // Return string containing refreshed order list
            return s_return;
        }
}
