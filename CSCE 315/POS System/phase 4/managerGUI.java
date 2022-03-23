import java.sql.*;
import java.util.Vector;
import java.awt.*;

import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import javax.swing.RowSorter;
import javax.swing.SortOrder;
import javax.swing.table.TableRowSorter;
import javax.swing.table.DefaultTableCellRenderer;

import java.util.Scanner;

public class managerGUI extends JFrame implements ActionListener {
    
    static JFrame manager_frame;
    static JTable table;
    static DefaultTableModel menu_table;

    static JTable t_inventory;
    static DefaultTableModel dt_inventory;

    static JTable t_target_amount;
    static DefaultTableModel dt_target_amount;

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
        String[] inventory_columns = { "Inventory ID", "Item Name", "Item Type", "Amount Available", "Target Amount","Units"};

        Vector<String[]> menu_content = new Vector<String[]>();
        Vector<String[]> inventory_content = new Vector<String[]>();
        try {
            // create a statement object
            Statement stmt = conn.createStatement();
            // create an SQL statement querying 10 menu item names
            String sqlStatement = "SELECT * FROM menu ORDER BY menu_id";
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
            String sqlStatement = "SELECT * FROM inventory ORDER BY inventory_id";
            // send statement to DBMS
            ResultSet result = stmt.executeQuery(sqlStatement);
            while (result.next()) {
                String[] row = { result.getString("inventory_id"), result.getString("item_name"),
                result.getString("item_type"),result.getString("amount_available"), result.getString("target_amount"), result.getString("units") };
                inventory_content.add(row);
            }

        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Error accessing Database.- inventory");
        }

        String[][] menu_data = new String[menu_content.size()][3];
        for (int i = 0; i < menu_content.size(); ++i) {
        menu_data[i] = menu_content.elementAt(i);
        }

        String[][] inventory_data = new String[inventory_content.size()][6];
        for (int i = 0; i < inventory_content.size(); ++i) {
            inventory_data[i] = inventory_content.elementAt(i);

        }

        /* Frame Declarations */

            // Manager GUI frame
            manager_frame = new JFrame("Manager GUI");
            manager_frame.setSize(1200, 800);
            manager_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            // View Inventory frame
            JFrame f_inventory_view = new JFrame("Menu View");
            f_inventory_view.setSize(600, 400);

        /* Tabs */

            /* Tab 1 - Ordering Popularity */ // TODO - retest all functionalities

                /* Text & Labels */

                    // Ordering Popularity table
                    JLabel l_order_pop = new JLabel("Menu Item Popularity by times ordered:");
                    JTable t_order_pop = new JTable(updateOrderPop("0001-01-01", "9999-12-31"));
                    JScrollPane p_order_pop_scroll = new JScrollPane(t_order_pop);

                    // Table sorting
                    TableRowSorter<TableModel> order_pop_sorter = new TableRowSorter<TableModel>(t_order_pop.getModel());
                    List<RowSorter.SortKey> order_pop_sortKeys = new ArrayList<>(1);
                    order_pop_sortKeys.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                    order_pop_sorter.setSortKeys(order_pop_sortKeys);
                    t_order_pop.setRowSorter(order_pop_sorter);

                    // Table column alignment
                    DefaultTableCellRenderer order_pop_left_renderer = new DefaultTableCellRenderer();
                    order_pop_left_renderer.setHorizontalAlignment(SwingConstants.LEFT);
                    t_order_pop.getColumnModel().getColumn(0).setCellRenderer(order_pop_left_renderer);
                    t_order_pop.getColumnModel().getColumn(2).setCellRenderer(order_pop_left_renderer);

                    // Start Date input
                    JLabel l_order_pop_start = new JLabel("Start Date ('yyyy-mm-dd'):");
                    JTextField t_order_pop_start = new JTextField(10);

                    // End Date input
                    JLabel l_order_pop_end = new JLabel("End Date ('yyyy-mm-dd'):");
                    JTextField t_order_pop_end = new JTextField(10);

                /* Buttons */

                    // Update Table button
                    JButton b_order_pop_update = new JButton("Update Table");
                    b_order_pop_update.addActionListener(e -> {
                        // Receive start/end dates from input fields
                        String s_order_pop_start = t_order_pop_start.getText();
                        String s_order_pop_end = t_order_pop_end.getText();

                        // Update data displayed in table
                        t_order_pop.setModel(updateOrderPop(s_order_pop_start, s_order_pop_end));

                        // Sort table
                        TableRowSorter<TableModel> order_pop_sorter_update = new TableRowSorter<TableModel>(t_order_pop.getModel());
                        List<RowSorter.SortKey> order_pop_sortKeys_update = new ArrayList<>(1);
                        order_pop_sortKeys_update.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                        order_pop_sorter_update.setSortKeys(order_pop_sortKeys_update);
                        t_order_pop.setRowSorter(order_pop_sorter_update);

                        // Table column alignment
                        DefaultTableCellRenderer order_pop_left_renderer_update = new DefaultTableCellRenderer();
                        order_pop_left_renderer_update.setHorizontalAlignment(SwingConstants.LEFT);
                        t_order_pop.getColumnModel().getColumn(0).setCellRenderer(order_pop_left_renderer_update);
                        t_order_pop.getColumnModel().getColumn(2).setCellRenderer(order_pop_left_renderer_update);

                        // Clear values in input fields
                        t_order_pop_start.setText("");
                        t_order_pop_end.setText("");
                    });

                    // Reset Table button
                    JButton b_order_pop_reset = new JButton("Reset");
                    b_order_pop_reset.addActionListener(e -> {
                        // Update data displayed in table
                        t_order_pop.setModel(updateOrderPop("0001-01-01", "9999-12-31"));

                        // Sort table
                        TableRowSorter<TableModel> order_pop_sorter_reset = new TableRowSorter<TableModel>(t_order_pop.getModel());
                        List<RowSorter.SortKey> order_pop_sortKeys_reset = new ArrayList<>(1);
                        order_pop_sortKeys_reset.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                        order_pop_sorter_reset.setSortKeys(order_pop_sortKeys_reset);
                        t_order_pop.setRowSorter(order_pop_sorter_reset);

                        // Table column alignment
                        DefaultTableCellRenderer order_pop_left_renderer_reset = new DefaultTableCellRenderer();
                        order_pop_left_renderer_reset.setHorizontalAlignment(SwingConstants.LEFT);
                        t_order_pop.getColumnModel().getColumn(0).setCellRenderer(order_pop_left_renderer_reset);
                        t_order_pop.getColumnModel().getColumn(2).setCellRenderer(order_pop_left_renderer_reset);

                        // Clear values in input fields
                        t_order_pop_start.setText("");
                        t_order_pop_end.setText("");
                    });

                /* Panels & Organization */

                    // Table label panel
                    JPanel p_order_pop_label = new JPanel();
                    p_order_pop_label.add(l_order_pop);

                    // Table panel
                    JPanel p_order_pop_table = new JPanel(new BorderLayout());
                    p_order_pop_table.add(p_order_pop_label, BorderLayout.NORTH);
                    p_order_pop_table.add(p_order_pop_scroll, BorderLayout.CENTER);

                    // Input Area panel
                    JPanel p_order_pop_input = new JPanel();
                    p_order_pop_input.add(l_order_pop_start);
                    p_order_pop_input.add(t_order_pop_start);
                    p_order_pop_input.add(l_order_pop_end);
                    p_order_pop_input.add(t_order_pop_end);
                    p_order_pop_input.add(b_order_pop_update);
                    p_order_pop_input.add(b_order_pop_reset);

                    // Order Popularity tab panel
                    JPanel p_order_pop = new JPanel(new BorderLayout());
                    p_order_pop.add(p_order_pop_table, BorderLayout.CENTER);
                    p_order_pop.add(p_order_pop_input, BorderLayout.SOUTH);

            /* Tab 2 - Inventory Popularity */ // TODO - retest all functionalities
                
                /* Text & Labels */

                    // Inventory usage chart
                    JLabel l_inv_usage = new JLabel("Inventory Item Popularity by item usage:");
                    JTable t_inv_usage = new JTable(updateInvUsage("2022-01-29", "2022-01-29"));
                    JScrollPane p_inv_usage_scroll = new JScrollPane(t_inv_usage);

                    // Table sorting
                    TableRowSorter<TableModel> inv_usage_sorter = new TableRowSorter<TableModel>(t_inv_usage.getModel());
                    List<RowSorter.SortKey> inv_usage_sortKeys = new ArrayList<>(1);
                    inv_usage_sortKeys.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                    inv_usage_sorter.setSortKeys(inv_usage_sortKeys);
                    t_inv_usage.setRowSorter(inv_usage_sorter);

                    // Table column alignment
                    DefaultTableCellRenderer inv_usage_left_renderer = new DefaultTableCellRenderer();
                    inv_usage_left_renderer.setHorizontalAlignment(SwingConstants.LEFT);
                    t_inv_usage.getColumnModel().getColumn(0).setCellRenderer(inv_usage_left_renderer);
                    t_inv_usage.getColumnModel().getColumn(2).setCellRenderer(inv_usage_left_renderer);
                    t_inv_usage.getColumnModel().getColumn(3).setCellRenderer(inv_usage_left_renderer);

                    // Start Date input
                    JLabel l_inv_usage_start = new JLabel("Start Date ('yyyy-mm-dd'):");
                    JTextField t_inv_usage_start = new JTextField(10);

                    // End Date input
                    JLabel l_inv_usage_end = new JLabel("End Date ('yyyy-mm-dd'):");
                    JTextField t_inv_usage_end = new JTextField(10);

                /* Buttons */

                    // Update Table button
                    JButton b_inv_usage_update = new JButton("Update Table");
                    b_inv_usage_update.addActionListener(e -> {
                        // Receive start/end dates from input fields
                        String s_inv_usage_start = t_inv_usage_start.getText();
                        String s_inv_usage_end = t_inv_usage_end.getText();

                        // Update data displayed in table
                        t_inv_usage.setModel(updateInvUsage(s_inv_usage_start, s_inv_usage_end));

                        // Sort table
                        TableRowSorter<TableModel> inv_usage_sorter_update = new TableRowSorter<TableModel>(t_inv_usage.getModel());
                        List<RowSorter.SortKey> inv_usage_sortKeys_update = new ArrayList<>(1);
                        inv_usage_sortKeys_update.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                        inv_usage_sorter_update.setSortKeys(inv_usage_sortKeys_update);
                        t_inv_usage.setRowSorter(inv_usage_sorter_update);

                        // Table column alignment
                        DefaultTableCellRenderer inv_usage_left_renderer_update = new DefaultTableCellRenderer();
                        inv_usage_left_renderer_update.setHorizontalAlignment(SwingConstants.LEFT);
                        t_inv_usage.getColumnModel().getColumn(0).setCellRenderer(inv_usage_left_renderer_update);
                        t_inv_usage.getColumnModel().getColumn(2).setCellRenderer(inv_usage_left_renderer_update);
                        t_inv_usage.getColumnModel().getColumn(3).setCellRenderer(inv_usage_left_renderer_update);

                        // Clear values in input fields
                        t_inv_usage_start.setText("");
                        t_inv_usage_end.setText("");
                    });

                    //Reset Table Button
                    JButton b_inv_usage_reset = new JButton("Reset");
                    b_inv_usage_reset.addActionListener(e -> {
                        // Update data displayed in table
                        t_inv_usage.setModel(updateInvUsage("2022-01-29", "2022-01-29"));

                        // Sort table
                        TableRowSorter<TableModel> inv_usage_sorter_reset = new TableRowSorter<TableModel>(t_inv_usage.getModel());
                        List<RowSorter.SortKey> inv_usage_sortKeys_reset = new ArrayList<>(1);
                        inv_usage_sortKeys_reset.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                        inv_usage_sorter_reset.setSortKeys(inv_usage_sortKeys_reset);
                        t_inv_usage.setRowSorter(inv_usage_sorter_reset);

                        // Table column alignment
                        DefaultTableCellRenderer inv_usage_left_renderer_reset = new DefaultTableCellRenderer();
                        inv_usage_left_renderer_reset.setHorizontalAlignment(SwingConstants.LEFT);
                        t_inv_usage.getColumnModel().getColumn(0).setCellRenderer(inv_usage_left_renderer_reset);
                        t_inv_usage.getColumnModel().getColumn(2).setCellRenderer(inv_usage_left_renderer_reset);
                        t_inv_usage.getColumnModel().getColumn(3).setCellRenderer(inv_usage_left_renderer_reset);

                        // Clear values in input fields
                        t_inv_usage_start.setText("");
                        t_inv_usage_end.setText("");
                    });
                   

                /* Panels & Organization */

                    // Table label panel
                    JPanel p_inv_usage_label = new JPanel();
                    p_inv_usage_label.add(l_inv_usage);

                    // Table panel
                    JPanel p_inv_usage_table = new JPanel(new BorderLayout());
                    p_inv_usage_table.add(p_inv_usage_label, BorderLayout.NORTH);
                    p_inv_usage_table.add(p_inv_usage_scroll, BorderLayout.CENTER);

                    // Input Area panel
                    JPanel p_inv_usage_input = new JPanel();
                    p_inv_usage_input.add(l_inv_usage_start);
                    p_inv_usage_input.add(t_inv_usage_start);
                    p_inv_usage_input.add(l_inv_usage_end);
                    p_inv_usage_input.add(t_inv_usage_end);
                    p_inv_usage_input.add(b_inv_usage_update);
                    p_inv_usage_input.add(b_inv_usage_reset);

                    // Order Popularity tab panel
                    JPanel p_inv_usage = new JPanel(new BorderLayout());
                    p_inv_usage.add(p_inv_usage_table, BorderLayout.CENTER);
                    p_inv_usage.add(p_inv_usage_input, BorderLayout.SOUTH);

            /* Tab 3 - Ordering Trends */
                /* Variables */
                
                /* Text & Labels */
                    // Ordering trends table
                    JLabel l_order_trends = new JLabel("Ordering Trends");
                    JTable t_order_trends = new JTable(updateOrderTrends("2022-01-02", "2022-01-08", "2022-01-09", "2022-01-15"));
                    JScrollPane p_order_trends_scroll = new JScrollPane(t_order_trends);

                    // Table sorting
                    TableRowSorter<TableModel> order_trends_sorter = new TableRowSorter<TableModel>(t_order_trends.getModel());
                    List<RowSorter.SortKey> order_trends_sortKeys = new ArrayList<>(1);
                    order_trends_sortKeys.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                    order_trends_sorter.setSortKeys(order_trends_sortKeys);
                    t_order_trends.setRowSorter(order_trends_sorter);

                    // Table column alignment
                    DefaultTableCellRenderer order_trends_left_renderer = new DefaultTableCellRenderer();
                    order_trends_left_renderer.setHorizontalAlignment(SwingConstants.LEFT);
                    t_order_trends.getColumnModel().getColumn(0).setCellRenderer(order_trends_left_renderer);
                    t_order_trends.getColumnModel().getColumn(2).setCellRenderer(order_trends_left_renderer);

                    // Start Date input 1
                    JLabel l_order_trends_start1 = new JLabel("First Start Date ('yyyy-mm-dd'):");
                    JTextField t_order_trends_start1 = new JTextField(10);

                    // End Date input 1
                    JLabel l_order_trends_end1 = new JLabel("First End Date ('yyyy-mm-dd'):");
                    JTextField t_order_trends_end1 = new JTextField(10);

                    // Start Date input 2
                    JLabel l_order_trends_start2 = new JLabel("Second Start Date ('yyyy-mm-dd'):");
                    JTextField t_order_trends_start2 = new JTextField(10);

                    // End Date input 2
                    JLabel l_order_trends_end2 = new JLabel("Second End Date ('yyyy-mm-dd'):");
                    JTextField t_order_trends_end2 = new JTextField(10);


                    

                /* Buttons */
                    // Update Table button
                        JButton b_order_trends_update = new JButton("Update Table");
                        b_order_trends_update.addActionListener(e -> {
                        // Receive start/end dates from input fields
                        String s_order_trends_start1 = t_order_trends_start1.getText();
                        String s_order_trends_end1 = t_order_trends_end1.getText();

                        String s_order_trends_start2 = t_order_trends_start2.getText();
                        String s_order_trends_end2 = t_order_trends_end2.getText();

                        // Update data displayed in table
                        t_order_trends.setModel(updateOrderTrends(s_order_trends_start1, s_order_trends_end1, s_order_trends_start2, s_order_trends_end2));

                        // Sort table
                        TableRowSorter<TableModel> order_trends_sorter_update = new TableRowSorter<TableModel>(t_order_trends.getModel());
                        List<RowSorter.SortKey> order_trends_sortKeys_update = new ArrayList<>(1);
                        order_trends_sortKeys_update.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                        order_trends_sorter_update.setSortKeys(order_trends_sortKeys_update);
                        t_order_trends.setRowSorter(order_trends_sorter_update);

                        // Table column alignment
                        DefaultTableCellRenderer order_trends_left_renderer_update = new DefaultTableCellRenderer();
                        order_trends_left_renderer_update.setHorizontalAlignment(SwingConstants.LEFT);
                        t_order_trends.getColumnModel().getColumn(0).setCellRenderer(order_trends_left_renderer_update);
                        t_order_trends.getColumnModel().getColumn(2).setCellRenderer(order_trends_left_renderer_update);

                        // Clear values in input fields
                        t_order_trends_start1.setText("");
                        t_order_trends_end1.setText("");  
                        t_order_trends_start2.setText("");
                        t_order_trends_end2.setText("");   
                    });

                    // Reset Table button
                    JButton b_order_trends_reset = new JButton("Reset");
                    b_order_trends_reset.addActionListener(e -> {
                    // Update data displayed in table
                    t_order_trends.setModel(updateOrderTrends("2022-01-02", "2022-01-08", "2022-01-09", "2022-01-15"));

                    // Sort table
                    TableRowSorter<TableModel> order_trends_sorter_reset = new TableRowSorter<TableModel>(t_order_trends.getModel());
                    List<RowSorter.SortKey> order_trends_sortKeys_reset = new ArrayList<>(1);
                    order_trends_sortKeys_reset.add(new RowSorter.SortKey(2, SortOrder.DESCENDING));
                    order_trends_sorter_reset.setSortKeys(order_trends_sortKeys_reset);
                    t_order_trends.setRowSorter(order_trends_sorter_reset);

                    // Table column alignment
                    DefaultTableCellRenderer order_trends_left_renderer_reset = new DefaultTableCellRenderer();
                    order_trends_left_renderer_reset.setHorizontalAlignment(SwingConstants.LEFT);
                    t_order_trends.getColumnModel().getColumn(0).setCellRenderer(order_trends_left_renderer_reset);
                    t_order_trends.getColumnModel().getColumn(2).setCellRenderer(order_trends_left_renderer_reset);

                    // Clear values in input fields
                    t_order_trends_start1.setText("");
                    t_order_trends_end1.setText("");
                });


                /* Panels & Organization */
                    // Table label panel
                    JPanel p_order_trends_label = new JPanel();
                    p_order_trends_label.add(l_order_trends);

                    // Table panel
                    JPanel p_order_trends_table = new JPanel(new BorderLayout());
                    p_order_trends_table.add(p_order_trends_label, BorderLayout.NORTH);
                    p_order_trends_table.add(p_order_trends_scroll, BorderLayout.CENTER);

                    // Input Area panel
                    JPanel p_order_trends_input = new JPanel(new GridLayout(10,1,6,6));
                    p_order_trends_input.add(l_order_trends_start1);
                    p_order_trends_input.add(t_order_trends_start1);
                    p_order_trends_input.add(l_order_trends_end1);
                    p_order_trends_input.add(t_order_trends_end1);
                    p_order_trends_input.add(l_order_trends_start2);
                    p_order_trends_input.add(t_order_trends_start2);
                    p_order_trends_input.add(l_order_trends_end2);
                    p_order_trends_input.add(t_order_trends_end2);
                    p_order_trends_input.add(b_order_trends_update);
                    p_order_trends_input.add(b_order_trends_reset);

                    // Order Popularity tab panel
                    JPanel p_order_trends = new JPanel(new BorderLayout());
                    p_order_trends.add(p_order_trends_table, BorderLayout.CENTER);
                    p_order_trends.add(p_order_trends_input, BorderLayout.SOUTH);
            
            /* Tab 4 - Inventory Management */ // TODO - retest all functionalities

                /* Tables */
                    dt_inventory = new DefaultTableModel(inventory_data, inventory_columns);
                    t_inventory = new JTable(dt_inventory);
                    t_inventory.setEnabled(false);
                    //create table that shows inv items not meeting target amount values
                    String[][] not_meeting = new String[inventory_content.size()][4];//changed
                    int j = 0;
                    for (int i = 0; i < inventory_data.length; ++i) {
                        if(Float.parseFloat(inventory_data[i][3]) < Float.parseFloat(inventory_data[i][4])) {
                            not_meeting[j][0] = inventory_data[i][0];
                            not_meeting[j][1] = inventory_data[i][1];
                            not_meeting[j][2] = Double.toString(Math.ceil(Double.parseDouble(inventory_data[i][4]) - Double.parseDouble(inventory_data[i][3])));
                            not_meeting[j][3] = inventory_data[i][5];
                            ++j;
                        }
                    }

                    String[] names_target_amount = {"Inventory ID", "Item Name", "# to reorder", "Units"};
                    dt_target_amount = new DefaultTableModel(not_meeting, names_target_amount);
                    t_target_amount = new JTable(dt_target_amount);
                    t_target_amount.setEnabled(false);
                    
                /* Text & Labels */

                    // Inventory display label
                    JLabel l_inv = new JLabel("Inventory");

                    // Restock Report label
                    JLabel l_restock_report = new JLabel("Restock Report");

                    // Modify Inventory
                    JLabel l_inv_mod = new JLabel("Modify Amount Available, Target Amount, or Item Name:");
                    JTextField t_inv_id = new JTextField();
                    JLabel l_inv_id = new JLabel("Enter Inventory ID to change:");
                    JTextField t_inv_name_num = new JTextField();
                    JLabel l_inv_np = new JLabel("Enter Name of Column to Change:");
                    JTextField t_inv_value = new JTextField();
                    JLabel l_inv_value = new JLabel("Enter New Value:");

                    // Add to Inventory
                    JLabel l_inv_add = new JLabel("Add new Inventory item:");
                    JLabel l_inv_add_id = new JLabel("Inventory ID: ");
                    JLabel l_inv_add_name = new JLabel("Item Name:");
                    JTextField t_inv_add_name = new JTextField();
                    JLabel l_inv_add_type = new JLabel("Item Type:");
                    JTextField t_inv_add_type = new JTextField();
                    JLabel l_inv_add_amount = new JLabel("Amount Available:");
                    JTextField t_inv_add_amount = new JTextField();
                    JLabel l_inv_add_target = new JLabel("Target Amount:");
                    JTextField t_inv_add_target = new JTextField();
                    JLabel l_inv_add_units = new JLabel("Container Units:");
                    JTextField t_inv_add_units = new JTextField();

                    // Remove from Inventory
                    JLabel l_inv_remove = new JLabel("Remove item from Inventory:");
                    JLabel l_inv_remove_id = new JLabel("Inventory ID:");
                    JTextField t_inv_remove_id = new JTextField();

                /* Buttons */

                    // Modify Data button
                    JButton b_inv_id = new JButton("Modify Data");
                    b_inv_id.addActionListener(e -> {
                        // Get the contents of the JTextArea component.
                        String s_inv_id = t_inv_id.getText();
                        String s_inv_name_num = t_inv_name_num.getText();
                        String s_inv_value = t_inv_value.getText();

                        // Restore to default
                        t_inv_id.setText("");
                        t_inv_name_num.setText("");
                        t_inv_value.setText("");
            
                        // Update values in table
                        for(int i = 0; i < inventory_data.length;++i) {
                
                            String value_at = t_inventory.getValueAt(i, 0).toString();
                            if(value_at.equals(s_inv_id)) { 
                                
                                if(s_inv_name_num.equals("Item Name")) {
                                    t_inventory.setValueAt(s_inv_value, i, 1);
                                    inventory_data[i][1] = s_inv_value;
                                    break;
                                }
                                else if(s_inv_name_num.equals("Item Type"))
                                {
                                    t_inventory.setValueAt(s_inv_value, i, 2);
                                    inventory_data[i][2] = s_inv_value;
                                    break;
                                }
                                    
                                else if(s_inv_name_num.equals("Amount Available"))
                                {
                                    t_inventory.setValueAt(s_inv_value, i, 3);
                                    inventory_data[i][3] = s_inv_value;
                                    break;
                                }
                                
                                else if(s_inv_name_num.equals("Target Amount"))
                                {
                                    t_inventory.setValueAt(s_inv_value, i, 4);
                                    inventory_data[i][4] = s_inv_value;
                                    break;
                                }
                                
                                else {
                                    t_inventory.setValueAt(s_inv_value, i, 5);
                                    inventory_data[i][5] = s_inv_value;
                                    break;
                                }
                                
                            }
                        }

                        refreshinventory(inventory_data, inventory_columns);
                        t_target_amount.repaint();

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

                        try{
                        // create a statement object
                        //Statement stmt2 = conns.createStatement();
                        String sqlStatement7;
                        String sqlStatement8;
                        String sqlStatement9;

                        // create an SQL statement
                        if(s_inv_name_num.equals("Item Name")) {
                            Statement stmt7 = conns3.createStatement();
                            sqlStatement7 = "UPDATE inventory SET item_name = '"+ s_inv_value
                            + "' WHERE inventory_id = " + Integer.parseInt(s_inv_id) ;
                            stmt7.executeUpdate(sqlStatement7);
                        }

                        else if(s_inv_name_num.equals("Target Amount")) {
                            Statement stmt8 = conns3.createStatement();
                            sqlStatement8 = "UPDATE inventory SET target_amount = "+ Float.parseFloat(s_inv_value)
                            + " WHERE inventory_id = " + Integer.parseInt(s_inv_id) ;
                            stmt8.executeUpdate(sqlStatement8);
                        }

                        else {
                            Statement stmt9 = conns3.createStatement();
                            sqlStatement9 = "UPDATE inventory SET amount_available = "+ Float.parseFloat(s_inv_value)
                            + " WHERE inventory_id = " + Integer.parseInt(s_inv_id) ;
                            stmt9.executeUpdate(sqlStatement9);
                        }

                        } catch (Exception c){
                            JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
                        }

                        try {
                            conns3.close();
                        } catch (Exception c) {
                            JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                        }
                    });

                    // Add to Inventory button - TODO: add button functionality
                    JButton b_inv_add = new JButton("Add to Inventory");
                    b_inv_add.addActionListener(e -> {
                        String s_inv_add_name = t_inv_add_name.getText();
                        String s_inv_add_type = t_inv_add_type.getText();
                        String s_inv_add_amount = t_inv_add_amount.getText();
                        String s_inv_add_target = t_inv_add_target.getText();
                        String s_inv_add_units = t_inv_add_units.getText();

                        t_inv_add_name.setText("");
                        t_inv_add_type.setText("");
                        t_inv_add_amount.setText("");
                        t_inv_add_target.setText("");
                        t_inv_add_units.setText("");

                        Connection conns10 = null;
                        try {
                            Class.forName("org.postgresql.Driver");
                            conns10 = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                                    "csce315910_14user", "drowssap14");
                        } catch (Exception l) {
                            l.printStackTrace();
                            System.err.println(l.getClass().getName() + ": " + l.getMessage());
                            System.exit(0);
                        }
                        

                        try{
                            // create a statement object
                            
                            String sqlStatement10;
                            
                            Statement stmt10 = conns10.createStatement();
                            sqlStatement10 = "INSERT INTO inventory (inventory_id, item_name, item_type, amount_available, target_amount, units) VALUES (" + (getLastInvID()+1) + ", '" + s_inv_add_name + "', '" + s_inv_add_type + "', " + Double.parseDouble(s_inv_add_amount) + " , " + Double.parseDouble(s_inv_add_target) + " , '" + s_inv_add_units + "' )" ;
                            stmt10.executeUpdate(sqlStatement10);

                        } catch (Exception m){
                            JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
                            }

                            try {
                                conns10.close();
                                JOptionPane.showMessageDialog(null, "Connection Closed.");
                            } catch (Exception b) {
                                JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                            }

                            String[] addrow = {Integer.toString(getLastInvID()),s_inv_add_name,s_inv_add_type, s_inv_add_amount, s_inv_add_target, s_inv_add_units};
                
                            dt_inventory.addRow(addrow);
                            dt_inventory.fireTableDataChanged();
                            String[][] inv_add_row = new String[inventory_data.length+1][6];
                            for(int i = 0; i < inventory_data.length; ++i) {
                                inv_add_row[i] = inventory_data[i];
                            }
                            inv_add_row[inventory_data.length] = new String[]{Integer.toString(getLastInvID()),s_inv_add_name, s_inv_add_type, s_inv_add_amount, s_inv_add_target, s_inv_add_units };
                            refreshinventory(inv_add_row, names_target_amount);
                            t_target_amount.repaint();
                        
                    });

                    // Remove from Inventory button - TODO: add button functionality
                    JButton b_inv_remove = new JButton("Remove from Inventory");
                    b_inv_remove.addActionListener(e -> {
                        
                        String s_delete_inv = t_inv_remove_id.getText();
                            t_inv_remove_id.setText("");
                        for(int i = 0; i < dt_inventory.getRowCount();++i) {
                            if(s_delete_inv.equals(dt_inventory.getValueAt(i, 0))) {
                                dt_inventory.removeRow(i);
                                break;
                            }
                        }
                        refreshinventory(inventory_data, names_target_amount);
                            t_target_amount.repaint();


                    Connection conns12 = null;
                    try {
                        Class.forName("org.postgresql.Driver");
                        conns12 = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                                "csce315910_14user", "drowssap14");
                    } catch (Exception o) {
                        o.printStackTrace();
                        System.err.println(o.getClass().getName() + ": " + o.getMessage());
                        System.exit(0);
                    }
                    JOptionPane.showMessageDialog(null, "Opened database successfully");


                    try{
                        // create a statement object
                        
                        String sqlStatement12;
                        
                        Statement stmt12 = conns12.createStatement();
                        sqlStatement12 = "DELETE FROM inventory WHERE inventory_id = " + s_delete_inv ;
                        stmt12.executeUpdate(sqlStatement12);

                    } catch (Exception p){
                        JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
                        }

                        try {
                            conns12.close();
                            JOptionPane.showMessageDialog(null, "Connection Closed.");
                        } catch (Exception u) {
                            JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                        }
                        
                    });

                /* Panels & Organization */

                    // Inventory label panel
                    JPanel p_label_inv = new JPanel();
                    p_label_inv.add(l_inv);

                    // Inventory table panel
                    JPanel p_inv_display = new JPanel(new BorderLayout());
                    p_inv_display.add(p_label_inv, BorderLayout.NORTH);
                    p_inv_display.add(new JScrollPane(t_inventory));

                    // Restock Report label panel
                    JPanel p_restock_report_label = new JPanel();
                    p_restock_report_label.add(l_restock_report);

                    // Restock Report panel
                    JPanel p_restock_report = new JPanel(new BorderLayout());
                    p_restock_report.add(p_restock_report_label, BorderLayout.NORTH);
                    p_restock_report.add(new JScrollPane(t_target_amount), BorderLayout.CENTER);

                    // Inventory Tables panel
                    JPanel p_inv_tables = new JPanel(new GridLayout(2,1,6,6));
                    p_inv_tables.add(p_inv_display);
                    p_inv_tables.add(p_restock_report);

                    // Modify Inventory label panel
                    JPanel p_inv_mod_label = new JPanel();
                    p_inv_mod_label.add(l_inv_mod);

                    // Inventory ID input panel
                    JPanel inv_id_panel = new JPanel(new BorderLayout());
                    inv_id_panel.add(l_inv_id, BorderLayout.NORTH);
                    inv_id_panel.add(t_inv_id, BorderLayout.CENTER);

                    // Inventory Column Name input panel
                    JPanel inv_np_panel = new JPanel(new BorderLayout());
                    inv_np_panel.add(l_inv_np, BorderLayout.NORTH);
                    inv_np_panel.add(t_inv_name_num, BorderLayout.CENTER);

                    // Inventory Value input panel
                    JPanel inv_val_panel = new JPanel(new BorderLayout());
                    inv_val_panel.add(l_inv_value, BorderLayout.NORTH);
                    inv_val_panel.add(t_inv_value, BorderLayout.CENTER);

                    // Modify Inventory grid panel
                    JPanel p_inv_mod_grid = new JPanel(new GridLayout(4,1,6,6));
                    p_inv_mod_grid.add(inv_id_panel);
                    p_inv_mod_grid.add(inv_np_panel); 
                    p_inv_mod_grid.add(inv_val_panel);
                    p_inv_mod_grid.add(b_inv_id);

                    // Modify Inventory panel
                    JPanel p_inv_mod = new JPanel(new BorderLayout());
                    p_inv_mod.add(p_inv_mod_label, BorderLayout.NORTH);
                    p_inv_mod.add(p_inv_mod_grid, BorderLayout.CENTER);

                    // Add to Inventory label panel
                    JPanel p_inv_add_label = new JPanel();
                    p_inv_add_label.add(l_inv_add);

                    // Add to Inventory Name panel
                    JPanel p_inv_add_name = new JPanel(new BorderLayout());
                    p_inv_add_name.add(l_inv_add_name, BorderLayout.NORTH);
                    p_inv_add_name.add(t_inv_add_name, BorderLayout.CENTER);

                    // Add to Inventory Type panel
                    JPanel p_inv_add_type = new JPanel(new BorderLayout());
                    p_inv_add_type.add(l_inv_add_type, BorderLayout.NORTH);
                    p_inv_add_type.add(t_inv_add_type, BorderLayout.CENTER);

                    // Add to Inventory Amount panel
                    JPanel p_inv_add_amount = new JPanel(new BorderLayout());
                    p_inv_add_amount.add(l_inv_add_amount, BorderLayout.NORTH);
                    p_inv_add_amount.add(t_inv_add_amount, BorderLayout.CENTER);

                    // Add to Inventory Target panel
                    JPanel p_inv_add_target = new JPanel(new BorderLayout());
                    p_inv_add_target.add(l_inv_add_target, BorderLayout.NORTH);
                    p_inv_add_target.add(t_inv_add_target, BorderLayout.CENTER);

                    // Add to Inventory Units panel
                    JPanel p_inv_add_units = new JPanel(new BorderLayout());
                    p_inv_add_units.add(l_inv_add_units, BorderLayout.NORTH);
                    p_inv_add_units.add(t_inv_add_units, BorderLayout.CENTER);

                    // Add to Inventory grid panel
                    JPanel p_inv_add_grid = new JPanel(new GridLayout(7,1,6,6));
                    p_inv_add_grid.add(l_inv_add_id);
                    p_inv_add_grid.add(p_inv_add_name);
                    p_inv_add_grid.add(p_inv_add_type);
                    p_inv_add_grid.add(p_inv_add_amount);
                    p_inv_add_grid.add(p_inv_add_target);
                    p_inv_add_grid.add(p_inv_add_units);
                    p_inv_add_grid.add(b_inv_add);

                    // Add to Inventory panel
                    JPanel p_inv_add = new JPanel(new BorderLayout());
                    p_inv_add.add(p_inv_add_label, BorderLayout.NORTH);
                    p_inv_add.add(p_inv_add_grid, BorderLayout.CENTER);

                    // Remove from Inventory label panel
                    JPanel p_inv_remove_label = new JPanel();
                    p_inv_remove_label.add(l_inv_remove);

                    // Remove from Inventory id panel
                    JPanel p_inv_remove_id = new JPanel(new BorderLayout());
                    p_inv_remove_id.add(l_inv_remove_id, BorderLayout.NORTH);
                    p_inv_remove_id.add(t_inv_remove_id, BorderLayout.CENTER);

                    // Remove from Inventory grid panel
                    JPanel p_inv_remove_grid = new JPanel(new GridLayout(2,1,6,6));
                    p_inv_remove_grid.add(p_inv_remove_id);
                    p_inv_remove_grid.add(b_inv_remove);
                    
                    // Remove from Inventory panel
                    JPanel p_inv_remove = new JPanel(new BorderLayout());
                    p_inv_remove.add(p_inv_remove_label, BorderLayout.NORTH);
                    p_inv_remove.add(p_inv_remove_grid, BorderLayout.CENTER);

                    // Inventory Controls panel
                    JPanel p_inv_control = new JPanel(new BorderLayout());
                    p_inv_control.add(p_inv_mod, BorderLayout.NORTH);
                    p_inv_control.add(p_inv_add, BorderLayout.CENTER);
                    p_inv_control.add(p_inv_remove, BorderLayout.SOUTH);

                /* Split Panel */

                    JSplitPane sp_inv_split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, p_inv_tables, p_inv_control);
                    // Modify height and width of split pane
                    sp_inv_split.setDividerLocation(800);
                    Dimension min_size2 = new Dimension(590, 390);
                    p_inv_tables.setMinimumSize(min_size2);
                    p_inv_control.setMinimumSize(min_size2);

            /* Tab 5 - Modify Menu */ // TODO - retest all functionalities

                /* Tables */

                    // Menu table
                    menu_table = new DefaultTableModel(menu_data, menu_columns);
                    table = new JTable(menu_table);
                    table.setEnabled(false);

                /* Text & Labels */

                    // Menu display label
                    JLabel l_menu = new JLabel("Menu");

                    // Modify Menu
                    JLabel l_menu_mod = new JLabel("Modify Menu Name or Price:");
                    JLabel l_menu_id = new JLabel("Enter Menu ID:");
                    JTextField t_menu_id = new JTextField();
                    JLabel l_menu_np = new JLabel("Enter Name of Column to Change:");
                    JTextField t_menu_np = new JTextField();
                    JLabel l_menu_value = new JLabel("Enter New Value:");
                    JTextField t_menu_value = new JTextField();

                    // Add to Menu
                    JLabel l_menu_add = new JLabel("Add new Menu item:");
                    JLabel l_add_id = new JLabel("Menu ID: " + Integer.toString(getLastMenuID() + 1));
                    JLabel l_add_name = new JLabel("Item Name:");
                    JTextField t_add_name = new JTextField();
                    JLabel l_add_price = new JLabel("Price:");
                    JTextField t_add_price = new JTextField();
                    JLabel l_add_items = new JLabel("Inventory Recipe:");
                    JTextArea t_add_items = new JTextArea();
                    t_add_items.setEditable(false);
                    t_add_items.setLineWrap(true);
                    JScrollPane p_add_items = new JScrollPane(t_add_items);

                    // Delete from Menu
                    JLabel l_menu_delete = new JLabel("Remove item from Menu:");
                    JLabel l_delete_id = new JLabel("Menu ID:");
                    JTextField t_delete_id = new JTextField();

                /* Buttons */

                    // Modify Menu button
                    JButton b_menu_id = new JButton("Modify Data");
                    b_menu_id.addActionListener(e -> {
                        // Get the contents of the JTextField component.
                        String s_menu_id = t_menu_id.getText();
                        String s_menu_np = t_menu_np.getText();
                        String s_menu_value = t_menu_value.getText();
            
                        // Restore to default
                        t_menu_id.setText("");
                        t_menu_np.setText("");
                        t_menu_value.setText("");
            
                        // Update values in table
                        for(int i = 0; i < menu_data.length;++i) {
                           
                            String value_at = table.getValueAt(i, 0).toString();
             
                            if(value_at.equals(s_menu_id)) {
                                
                                if(s_menu_np.equals("Menu Name")) {
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
                        
                        try{
                        // create a statement object
                        String sqlStatement2;
                        String sqlStatement3;
                        
                        // create an SQL statement 
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
                        
                        
                        } catch (Exception a){
                        JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
                        }
            
                        try {
                            conns.close();
                        } catch (Exception a) {
                            JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                        }
                    });

                    // Add to Menu button - TODO: add updates to recipe table
                    JButton b_add_row = new JButton("Add entry");
                    b_add_row.addActionListener(e -> {
                        // Get the contents of the JTextField component.
                        String s_menu_id = Integer.toString(getLastMenuID() + 1);
                        String s_menu_np = t_add_name.getText();
                        String s_menu_value = t_add_price.getText();
            
                        // restore to default
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
            
                         try{
                            // create a statement object
                            
                            String sqlStatement5;
                            
                            Statement stmt5 = conns2.createStatement();
                            sqlStatement5 = "INSERT INTO menu (menu_id, menu_name, price) VALUES (" + Integer.parseInt(s_menu_id) + ", '" + s_menu_np + "', " + Float.parseFloat(s_menu_value) + ")" ;
                            stmt5.executeUpdate(sqlStatement5);

                            // Find most recent recipe ID value
                            int prev_recipe_id = 0;
                            Statement stmt_recipe_id = conns2.createStatement();
                            String s_recipe_id = "SELECT * FROM recipe ORDER BY recipe_id DESC LIMIT 1";
                            ResultSet res_recipe_id = stmt_recipe_id.executeQuery(s_recipe_id);
                            while (res_recipe_id.next()) {
                                prev_recipe_id = Integer.parseInt(res_recipe_id.getString("recipe_id"));
                            }

                            // Pull and parse order contents from user input
                            String s_recipe_contents = t_add_items.getText();
                            Scanner scanner = new Scanner(s_recipe_contents);
                            List<String> words= new ArrayList<>();
                            while(scanner.hasNextLine()){
                                Scanner line= new Scanner(scanner.nextLine());
                                while (line.hasNext()){
                                    words.add(line.next());
                                }
                                line.close();
                            }
                            scanner.close();

                            // Enter recipe information into the database
                            Statement stat_add_recipe;
                            String s_add_recipe;
                            for(int i=0; i<words.size(); i+=2){
                                stat_add_recipe= conns2.createStatement();
                                s_add_recipe = "INSERT INTO recipe(recipe_id, inventory_id, menu_id, quantity) VALUES(" + (prev_recipe_id + 1) + ", " + Integer.parseInt(words.get(i)) + ", " + Integer.parseInt(s_menu_id) + ", " + Double.parseDouble(words.get(i+1)) + ")";
                                stat_add_recipe.executeUpdate(s_add_recipe);
                                prev_recipe_id++;
                            }
            
                        } catch (Exception a){
                            JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
                            }
            
                            try {
                                conns2.close();
                            } catch (Exception b) {
                                JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                            }
            
                        String[] addrow = {s_menu_id,s_menu_np,s_menu_value};
                        menu_table.addRow(addrow);
                        table.revalidate();
                        table.repaint();

                        // Update next menu ID label
                        l_add_id.setText("Menu ID: " + Integer.toString(getLastMenuID() + 1));
                    });

                    // Select from Inventory button
                    JButton b_inv_select = new JButton("Select from Inventory");
                    b_inv_select.addActionListener(e -> {
                        f_inventory_view.setLocationRelativeTo(null);
                        f_inventory_view.setVisible(true);
                    });

                    // Reset Recipe button
                    JButton b_recipe_reset = new JButton("Reset");
                    b_recipe_reset.addActionListener(e -> {
                        t_add_items.setText("");
                    });

                    // Remove from Menu button
                    JButton b_delete_row = new JButton("Delete entry");
                    b_delete_row.addActionListener(e -> {
                        String s_delete_id = t_delete_id.getText();
                        t_delete_id.setText("");
                        for(int i = 0; i < menu_table.getRowCount();++i) {
                            if(s_delete_id.equals(menu_table.getValueAt(i, 0))) {
                                menu_table.removeRow(i);
                                break;
                            }
                        }
        
                        Connection conns8 = null;
                        try {
                            Class.forName("org.postgresql.Driver");
                            conns8 = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                                    "csce315910_14user", "drowssap14");
                        } catch (Exception f) {
                            f.printStackTrace();
                            System.err.println(f.getClass().getName() + ": " + f.getMessage());
                            System.exit(0);
                        }
            
                        try{
                            // create a statement object
                            String sqlStatement8;
                            Statement stmt8 = conns8.createStatement();
                            sqlStatement8 = "DELETE FROM menu WHERE menu_id = " + s_delete_id ;
                            stmt8.executeUpdate(sqlStatement8);
            
                        } catch (Exception g){
                            JOptionPane.showMessageDialog(null,"Error accessing Database.- menu");
                        }
        
                        try {
                            conns8.close();
                        } catch (Exception b) {
                            JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                        }
        
                        // Update next menu ID string if necessary
                        l_add_id.setText("Menu ID: " + Integer.toString(getLastMenuID() + 1));
                    });
                    
                /* Panels & Organization */

                    // Menu Table label panel
                    JPanel p_menu_label = new JPanel();
                    p_menu_label.add(l_menu);

                    // Menu Table panel
                    JPanel p_mod_menu_items = new JPanel(new BorderLayout());
                    p_mod_menu_items.add(p_menu_label, BorderLayout.NORTH);
                    p_mod_menu_items.add(new JScrollPane(table), BorderLayout.CENTER);

                    // Modify Menu label panel
                    JPanel p_mod_menu_label = new JPanel();
                    p_mod_menu_label.add(l_menu_mod);

                    // Modify Menu ID panel
                    JPanel p_mod_menu_id = new JPanel(new BorderLayout());
                    p_mod_menu_id.add(l_menu_id, BorderLayout.NORTH);
                    p_mod_menu_id.add(t_menu_id, BorderLayout.CENTER);

                    // Modify Menu column panel
                    JPanel p_mod_menu_column = new JPanel(new BorderLayout());
                    p_mod_menu_column.add(l_menu_np, BorderLayout.NORTH);
                    p_mod_menu_column.add(t_menu_np, BorderLayout.CENTER);

                    // Modify Menu value panel
                    JPanel p_mod_menu_value = new JPanel(new BorderLayout());
                    p_mod_menu_value.add(l_menu_value, BorderLayout.NORTH);
                    p_mod_menu_value.add(t_menu_value, BorderLayout.CENTER);

                    // Modify Menu grid panel
                    JPanel p_mod_menu_grid = new JPanel(new GridLayout(4,1,6,6));
                    p_mod_menu_grid.add(p_mod_menu_id);
                    p_mod_menu_grid.add(p_mod_menu_column);
                    p_mod_menu_grid.add(p_mod_menu_value);
                    p_mod_menu_grid.add(b_menu_id);

                    // Modify Menu panel
                    JPanel p_mod_menu = new JPanel(new BorderLayout());
                    p_mod_menu.add(p_mod_menu_label, BorderLayout.NORTH);
                    p_mod_menu.add(p_mod_menu_grid, BorderLayout.CENTER);

                    // Add to Menu label panel
                    JPanel p_menu_add_label = new JPanel();
                    p_menu_add_label.add(l_menu_add);

                    // Add to Menu name panel
                    JPanel p_menu_add_name = new JPanel(new BorderLayout());
                    p_menu_add_name.add(l_add_name, BorderLayout.NORTH);
                    p_menu_add_name.add(t_add_name, BorderLayout.CENTER);

                    // Add to Menu price panel
                    JPanel p_menu_add_price = new JPanel(new BorderLayout());
                    p_menu_add_price.add(l_add_price, BorderLayout.NORTH);
                    p_menu_add_price.add(t_add_price, BorderLayout.CENTER);

                    // Add to Menu text fields panel
                    JPanel p_menu_add_text = new JPanel(new GridLayout(3,1,6,6));
                    p_menu_add_text.add(l_add_id);
                    p_menu_add_text.add(p_menu_add_name);
                    p_menu_add_text.add(p_menu_add_price);

                    // Add to Menu items panel
                    JPanel p_menu_add_items = new JPanel(new BorderLayout());
                    p_menu_add_items.add(l_add_items, BorderLayout.NORTH);
                    p_menu_add_items.add(p_add_items, BorderLayout.CENTER);
                    p_menu_add_items.add(b_recipe_reset, BorderLayout.EAST);

                    // Add to Menu buttons panel
                    JPanel p_menu_add_buttons = new JPanel(new GridLayout(1,2,6,6));
                    p_menu_add_buttons.add(b_add_row);
                    p_menu_add_buttons.add(b_inv_select);

                    // Add to menu grid panel
                    JPanel p_menu_add_grid = new JPanel(new GridLayout(3,1,6,6));
                    p_menu_add_grid.add(p_menu_add_text);
                    p_menu_add_grid.add(p_menu_add_items);
                    p_menu_add_grid.add(p_menu_add_buttons);

                    // Add to menu panel
                    JPanel p_menu_add = new JPanel(new BorderLayout());
                    p_menu_add.add(p_menu_add_label, BorderLayout.NORTH);
                    p_menu_add.add(p_menu_add_grid, BorderLayout.CENTER);

                    // Remove from Menu label panel
                    JPanel p_menu_remove_label = new JPanel();
                    p_menu_remove_label.add(l_menu_delete);

                    // Remove from Menu ID panel
                    JPanel p_menu_remove_id = new JPanel(new BorderLayout());
                    p_menu_remove_id.add(l_delete_id, BorderLayout.NORTH);
                    p_menu_remove_id.add(t_delete_id, BorderLayout.CENTER);

                    // Remove from Menu grid panel
                    JPanel p_menu_remove_grid = new JPanel(new GridLayout(2,1,6,6));
                    p_menu_remove_grid.add(p_menu_remove_id);
                    p_menu_remove_grid.add(b_delete_row);

                    // Remove from Menu panel
                    JPanel p_menu_remove = new JPanel(new BorderLayout());
                    p_menu_remove.add(p_menu_remove_label, BorderLayout.NORTH);
                    p_menu_remove.add(p_menu_remove_grid, BorderLayout.CENTER);
                    
                    // Menu Controls panel
                    JPanel p_menu_controls = new JPanel(new BorderLayout());
                    p_menu_controls.add(p_mod_menu, BorderLayout.NORTH);
                    p_menu_controls.add(p_menu_remove, BorderLayout.SOUTH);
                    p_menu_controls.add(p_menu_add, BorderLayout.CENTER);

                /* Split Pane */
                    JSplitPane mod_menu_split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, p_mod_menu_items, p_menu_controls);
                    mod_menu_split.setDividerLocation(800);
                    p_menu_controls.setMinimumSize(min_size2);
                    p_mod_menu_items.setMinimumSize(min_size2);

            /* Tab & Frame Organization */

                // Collect all tabs into main tabbed pane
                JTabbedPane tabs = new JTabbedPane();
                tabs.addTab("Ordering Popularity", p_order_pop);
                tabs.addTab("Inventory Popularity", p_inv_usage);
                tabs.addTab("Ordering Trends", p_order_trends);
                tabs.addTab("Inventory Management", sp_inv_split);
                tabs.addTab("Modify Menu", mod_menu_split);
                manager_frame.add(tabs);
                manager_frame.setLocationRelativeTo(null);
                manager_frame.setVisible(true);

        /* Inventory Selection Frame implementation */

            /* Text & Labels */

                // Inventory Information (scrolling text box)
                JTextArea t_inv_select = new JTextArea(retrieveInv());
                t_inv_select.setLineWrap(true);
                t_inv_select.setWrapStyleWord(true);
                t_inv_select.setEditable(false);
                JScrollPane p_inv_select_scroll = new JScrollPane(t_inv_select);

                // Inventory ID
                JLabel l_inv_select_id = new JLabel("Inventory ID:");
                JTextField t_inv_select_id = new JTextField(10);

                // Inventory item Quantity
                JLabel l_inv_select_quantity = new JLabel("Quantity:");
                JTextField t_inv_select_quantity = new JTextField(10);

            /* Buttons */

                // Confirmation button
                JButton b_menu_confirm = new JButton("Add to Recipe");
                b_menu_confirm.addActionListener(e->{
                    // Update display in Order Contents text area
                    String new_inv_id = t_inv_select_id.getText();
                    String new_quantity = t_inv_select_quantity.getText();
                    t_add_items.append(new_inv_id + " " + new_quantity + "\n");

                    // Reset text fields and close panel
                    t_inv_select_id.setText("");
                    t_inv_select_quantity.setText("");
                    f_inventory_view.dispose();
                });

                // Cancel button
                JButton b_menu_select_cancel = new JButton("Cancel");
                b_menu_select_cancel.addActionListener(e->{
                    // Reset text fields and close panel
                    t_inv_select_id.setText("");
                    t_inv_select_quantity.setText("");
                    f_inventory_view.dispose();
                });

            /* Panels & Organization */

                // Inventory ID & Quantity panel (with buttons)
                JPanel p_inv_select_options = new JPanel();
                p_inv_select_options.add(l_inv_select_id);
                p_inv_select_options.add(t_inv_select_id);
                p_inv_select_options.add(l_inv_select_quantity);
                p_inv_select_options.add(t_inv_select_quantity);
                p_inv_select_options.add(b_menu_confirm);
                p_inv_select_options.add(b_menu_select_cancel);

                // Inventory Selection panel
                JPanel p_inv_select = new JPanel(new BorderLayout());
                p_inv_select.add(p_inv_select_scroll, BorderLayout.CENTER);
                p_inv_select.add(p_inv_select_options, BorderLayout.SOUTH);

                // Add main panel to frame
                f_inventory_view.add(p_inv_select);

        // closing the connection
        try {
            conn.close();
            JOptionPane.showMessageDialog(null, "Connection Closed.");
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
        }
    }

        /* Functions */

            // Inventory Table Function
            static public void refreshinventory(String[][] inventory_data, String[] inventory_columns) {
                String[][] not_meetings = new String[inventory_data.length][4];//changed
                int j = 0;
                for (int i = 0; i < inventory_data.length; ++i) {
                    if(Float.parseFloat(inventory_data[i][3]) < Float.parseFloat(inventory_data[i][4])) {
                        not_meetings[j][0] = inventory_data[i][0];
                        not_meetings[j][1] = inventory_data[i][1];
                        not_meetings[j][2] = Double.toString(Math.ceil(Double.parseDouble(inventory_data[i][4]) - Double.parseDouble(inventory_data[i][3])));
                        not_meetings[j][3] = inventory_data[i][5];
                        ++j;
                    }
                }

                String[] names_target_amount = {"Inventory ID","Item Name", "# to reorder", "Units"};
                dt_target_amount = new DefaultTableModel(not_meetings, names_target_amount);
                t_target_amount.setModel(dt_target_amount);
            }

            // Ordering Popularity Table function
            static DefaultTableModel updateOrderPop(String s_start, String s_end) {
                // Set up new table model
                DefaultTableModel model = new DefaultTableModel(new String[]{"Menu ID", "Name", "Times Ordered"}, 0) {
                    @Override
                    public boolean isCellEditable(int row, int column) {
                        return false;
                    }
                    public Class getColumnClass(int column) {
                        switch (column) {
                            case 0:
                                return Integer.class;
                            case 1:
                                return String.class;
                            case 2:
                                return Integer.class;
                            default:
                                return String.class;
                        }
                    }
                };

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
                    // Connect to database menu table to get a set of all menu_id and corresponding name values
                    Statement stat_read_menu = conn_function.createStatement();
                    String s_read_menu = "SELECT menu_id, menu_name FROM menu ORDER BY menu_id";
                    ResultSet res_read_menu = stat_read_menu.executeQuery(s_read_menu);

                    // Parse through each menu listing's data
                    while (res_read_menu.next()) {
                        // Collect menu listing's menu ID and name values
                        int menu_id = Integer.parseInt(res_read_menu.getString("menu_id"));
                        String menu_name = res_read_menu.getString("menu_name");
                        int num_ordered = 0;

                        // Connect to database trends table between two set dates to calculate total number ordered by menu_id
                        Statement stat_order_count = conn_function.createStatement();
                        String s_order_count = "SELECT times_ordered FROM trends WHERE trend_date BETWEEN '" + s_start + "' and '" + s_end + "' AND menu_id=" + menu_id;
                        ResultSet res_order_count = stat_order_count.executeQuery(s_order_count);

                        // Parse through each trend listing's data
                        while (res_order_count.next()) {
                            num_ordered += Integer.parseInt(res_order_count.getString("times_ordered"));
                        }

                        // Add menu item's ID, name, and total number ordered to table
                        model.addRow(new Object[]{menu_id, menu_name, num_ordered});
                    }

                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null,"Error accessing Database.");
                }

                // Close connection to database
                try {
                    conn_function.close();
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                }

                // Return model containing order popularity data
                return model;
            }

            // Inventory Popularity Table Function
            static DefaultTableModel updateInvUsage(String s_start, String s_end) {
                // Set up new table model
                DefaultTableModel model = new DefaultTableModel(new String[]{"Item ID", "Item Name", "Times Used", "Amount Used"}, 0) {
                    @Override
                    public boolean isCellEditable(int row, int column) {
                        return false;
                    }
                    public Class getColumnClass(int column) {
                        switch (column) {
                            case 0:
                                return Integer.class;
                            case 1:
                                return String.class;
                            case 2:
                                return Integer.class;
                            case 3:
                                return Double.class;
                            default:
                                return String.class;
                        }
                    }
                };

                // Open connection to database
                Connection conn_func = null;
                try {
                    Class.forName("org.postgresql.Driver");
                    conn_func = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                    "csce315910_14user", "drowssap14");
                } catch (Exception e) {
                    e.printStackTrace();
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    System.exit(0);
                }

                try {
                    
                    // Connect to database inventory table to count rows
                    Statement stat_count = conn_func.createStatement();
                    String s_count = "SELECT * FROM inventory";
                    ResultSet res_count = stat_count.executeQuery(s_count);
                    int count=0;
                    while(res_count.next()){
                        count++;
                    }
                    
                    //Initialize array to hold values based on inventory id
                    double item_usage[]= new double[count];
                    int times_used[]= new int[count];
                    
                    // Connect to database trends table to get a set of all menu_id and times_ordered values in the interval of dates provided
                    Statement stat_trend_times = conn_func.createStatement();
                    String s_trend_times = "SELECT menu_id, times_ordered FROM trends WHERE trend_date BETWEEN '" + s_start + "' and '" + s_end + "'";
                    ResultSet res_trend_times = stat_trend_times.executeQuery(s_trend_times);

                    // Parse through each trends listing's data
                    while (res_trend_times.next()) {
                        // Collect menu listing's menu ID and times ordered values
                        int menu_id = Integer.parseInt(res_trend_times.getString("menu_id"));
                        int times_ordered = Integer.parseInt(res_trend_times.getString("times_ordered"));

                        // Connect to database recipe table for a certain menu_id
                        Statement stat_menu_recipe = conn_func.createStatement();
                        String s_menu_recipe = "SELECT inventory_id, quantity FROM recipe WHERE menu_id=" + menu_id;
                        ResultSet res_menu_recipe = stat_menu_recipe.executeQuery(s_menu_recipe);

                        // Parse through each recipe listing's data
                        while (res_menu_recipe.next()) {
                            // Collect recipe listing's inventory ID and quantity values
                            int inventory_id = Integer.parseInt(res_menu_recipe.getString("inventory_id"));
                            double quantity = Double.parseDouble(res_menu_recipe.getString("quantity"));
                            
                            //add item usage
                            item_usage[inventory_id]+= (times_ordered*quantity);

                            //add times used
                            times_used[inventory_id]+= times_ordered;
                        }
                        
                    }

                    String item_name="";

                    for(int i=0; i< item_usage.length; i++){
                        if(item_usage[i]>0 && times_used[i]>0){
                            // Connect to database inventory table to get item names
                            Statement stat_item_name = conn_func.createStatement();
                            String s_item_name = "SELECT item_name FROM inventory WHERE inventory_id="+i;
                            ResultSet res_item_name = stat_item_name.executeQuery(s_item_name);
                            while(res_item_name.next()){
                                item_name= res_item_name.getString("item_name");
                            }
                            // Add to table
                            model.addRow(new Object[]{i, item_name, times_used[i], item_usage[i]});
                        }
                    }


                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null,"Error accessing Database~ inventory usage.");
                }

                // Close connection to database
                try {
                    conn_func.close();
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                }

                // Return model containing order popularity data
                return model;
            }

            // Last Used Menu ID Retrieval Function
            static int getLastMenuID() {
                // Set up integer for menu ID
                int last_id = 0;

                // Open connection to database
                Connection conn_func = null;
                try {
                    Class.forName("org.postgresql.Driver");
                    conn_func = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                    "csce315910_14user", "drowssap14");
                } catch (Exception e) {
                    e.printStackTrace();
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    System.exit(0);
                }

                // Query menu table for last used menu ID
                try {
                    Statement stat_last_menu = conn_func.createStatement();
                    String s_last_menu = "SELECT menu_id FROM menu ORDER BY menu_id DESC LIMIT 1";
                    ResultSet res_last_menu = stat_last_menu.executeQuery(s_last_menu);
                    while(res_last_menu.next()){
                        last_id = Integer.parseInt(res_last_menu.getString("menu_id"));
                    }

                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null,"Error accessing Database~ inventory usage.");
                }

                // Close connection to database
                try {
                    conn_func.close();
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                }

                // Return retrieved menu ID
                return last_id;
            }
    
        static int getLastInvID() {
                // Set up integer for menu ID
                int last_id = 0;

                // Open connection to database
                Connection conn_func = null;
                try {
                    Class.forName("org.postgresql.Driver");
                    conn_func = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                    "csce315910_14user", "drowssap14");
                } catch (Exception e) {
                    e.printStackTrace();
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    System.exit(0);
                }

                // Query menu table for last used menu ID
                try {
                    Statement stat_last_inv = conn_func.createStatement();
                    String s_last_inv = "SELECT inventory_id FROM inventory ORDER BY inventory_id DESC LIMIT 1";
                    ResultSet res_last_inv = stat_last_inv.executeQuery(s_last_inv);
                    while(res_last_inv.next()){
                        last_id = Integer.parseInt(res_last_inv.getString("inventory_id"));
                    }

                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null,"Error accessing Database~ inventory usage.");
                }

                // Close connection to database
                try {
                    conn_func.close();
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                }

                // Return retrieved menu ID
                return last_id;
            }

            // Update Order Trends
            static DefaultTableModel updateOrderTrends(String s_start1, String s_end1, String s_start2, String s_end2 ) {
                // Set up new table model
                DefaultTableModel model = new DefaultTableModel(new String[]{"Menu ID", "Name", "Trend Status (%)"}, 0) {
                    @Override
                    public boolean isCellEditable(int row, int column) {
                        return false;
                    }
                    public Class getColumnClass(int column) {
                        switch (column) {
                            case 0:
                                return Integer.class;
                            case 1:
                                return String.class;
                            case 2:
                                return Double.class;
                            default:
                                return String.class;
                        }
                    }
                };
                

                // Open connection to database
                Connection conn_function1 = null;
                try {
                    Class.forName("org.postgresql.Driver");
                    conn_function1 = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                    "csce315910_14user", "drowssap14");
                } catch (Exception e) {
                    e.printStackTrace();
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    System.exit(0);
                }

                try {
                    // Connect to database menu table to get total revenue
                    Statement stat_read_menu1 = conn_function1.createStatement();
                    String s_read_menu1 = "SELECT * FROM menu ORDER BY menu_id";
                    ResultSet res_read_menu1 = stat_read_menu1.executeQuery(s_read_menu1);
                    double total_rev1 = 0;
                    double total_rev2 = 0;
                    

                    while(res_read_menu1.next()){
                        int menu_id = Integer.parseInt(res_read_menu1.getString("menu_id"));
                        double price = Double.parseDouble(res_read_menu1.getString("price"));
                        Statement stat_order_count = conn_function1.createStatement();
                        String s_order_count = "SELECT times_ordered FROM trends WHERE trend_date BETWEEN '" + s_start1 + "' and '" + s_end1 + "' AND menu_id=" + menu_id;
                        ResultSet res_order_count = stat_order_count.executeQuery(s_order_count);
                        while(res_order_count.next()){
                            total_rev1 += (Integer.parseInt(res_order_count.getString("times_ordered")) * price);
                        }

                        Statement stat_order_count2 = conn_function1.createStatement();
                        String s_order_count2 = "SELECT times_ordered FROM trends WHERE trend_date BETWEEN '" + s_start2 + "' and '" + s_end2 + "' AND menu_id=" + menu_id;
                        ResultSet res_order_count2 = stat_order_count.executeQuery(s_order_count);
                        while(res_order_count2.next()){
                            total_rev2 += (Integer.parseInt(res_order_count2.getString("times_ordered")) * price);
                        }
                        

                    }

                    // Connect to database menu table to get a set of all menu_id and corresponding name values
                    Statement stat_read_menu2 = conn_function1.createStatement();
                    String s_read_menu2 = "SELECT * FROM menu ORDER BY menu_id";
                    ResultSet res_read_menu2 = stat_read_menu2.executeQuery(s_read_menu2);

                    // Parse through each menu listing's data
                    while (res_read_menu2.next()) {
                        // Collect menu listing's menu ID and name values
                        int menu_id = Integer.parseInt(res_read_menu2.getString("menu_id"));
                        double price = Double.parseDouble(res_read_menu2.getString("price"));
                        double revenue = 0;
                        double revenue2 = 0;
                        String menu_name = res_read_menu2.getString("menu_name");
                    
                        // Connect to database trends table between two set dates to calculate total number ordered by menu_id
                        Statement stat_order_count = conn_function1.createStatement();
                        String s_order_count = "SELECT times_ordered FROM trends WHERE trend_date BETWEEN '" + s_start1 + "' and '" + s_end1 + "' AND menu_id=" + menu_id;
                        ResultSet res_order_count = stat_order_count.executeQuery(s_order_count);

                        // Parse through each trend listing's data
                        while (res_order_count.next()) {
                            revenue += (Integer.parseInt(res_order_count.getString("times_ordered")) * price);
                        }

                        // Connect to database trends table between two set dates to calculate total number ordered by menu_id
                        Statement stat_order_count2 = conn_function1.createStatement();
                        String s_order_count2 = "SELECT times_ordered FROM trends WHERE trend_date BETWEEN '" + s_start2 + "' and '" + s_end2 + "' AND menu_id=" + menu_id;
                        ResultSet res_order_count2 = stat_order_count2.executeQuery(s_order_count2);

                        // Parse through each trend listing's data
                        while (res_order_count2.next()) {
                            revenue2 += (Integer.parseInt(res_order_count2.getString("times_ordered")) * price);
                        }

                        // Add menu item's ID, name, and total number ordered to table
                        double percent_total_rev1 = revenue/total_rev1 * 100;
                        double percent_total_rev2 = revenue2/total_rev2 * 100;
                        double change = percent_total_rev2 - percent_total_rev1;
                        model.addRow(new Object[]{menu_id, menu_name, change});
                    }

                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null,"Error accessing Database.");
                }

                // Close connection to database
                try {
                    conn_function1.close();
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                }

                // Return model containing order popularity data
                return model;
            }

            // Retrieve inventory table function
            static String retrieveInv() {
                // Set up string to return with inventory values when done
                String s_return = "";

                // Open connection to database
                Connection conn_func = null;
                try {
                    Class.forName("org.postgresql.Driver");
                    conn_func = DriverManager.getConnection("jdbc:postgresql://csce-315-db.engr.tamu.edu/csce315910_14db",
                    "csce315910_14user", "drowssap14");
                } catch (Exception e) {
                    e.printStackTrace();
                    System.err.println(e.getClass().getName() + ": " + e.getMessage());
                    System.exit(0);
                }

                try {

                    // Query inventory table for ID and name
                    Statement stmt_inv = conn_func.createStatement();
                    String s_inv = "SELECT * FROM inventory ORDER BY inventory_id";
                    ResultSet res_inv = stmt_inv.executeQuery(s_inv);
                    while (res_inv.next()) {
                        s_return += res_inv.getString("inventory_id") + " - " + res_inv.getString("item_name") + "\n";
                    }

                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null,"Error accessing Database~ inventory usage.");
                }

                // Close connection to database
                try {
                    conn_func.close();
                } catch (Exception e) {
                    JOptionPane.showMessageDialog(null, "Connection NOT Closed.");
                }

                // Return string when filled with inventory values
                return s_return;
            }

            // if button is pressed
            public void actionPerformed(ActionEvent e) {
                String s = e.getActionCommand();
                if (s.equals("Close")) {
                    manager_frame.dispose();
                }
            }
        }

