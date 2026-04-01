using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;


namespace Laborator2
{
    public partial class Form1 : Form
    {
        private readonly string _connectionString = ConfigurationManager.ConnectionStrings["cnString"].ConnectionString;

        private readonly DataSet _dsP = new DataSet();
        private readonly DataSet _dsC = new DataSet();
        SqlDataAdapter _parentAdapter;
        SqlDataAdapter _childAdapter;
        BindingSource _bsParent;
        BindingSource _bsChild;

        private SqlCommand _selectCommand;

        public Form1()
        {
            InitializeComponent();
            Text = @"Laboratorul2";
        }

        public sealed override string Text
        {
            get { return base.Text; }
            set { base.Text = value; }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(_connectionString))
                {
                    tableChild.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                    tableChild.MultiSelect = false;
                    tableChild.ReadOnly = true;
                    tableParent.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                    tableParent.MultiSelect = false;
                    tableParent.ReadOnly = true;
                    tableParent.AutoGenerateColumns = true;
                    tableChild.AutoGenerateColumns = true;

                    conn.Open();
                    MessageBox.Show(@"Starea conexiunii: " + conn.State);
                    _parentAdapter = new SqlDataAdapter(ConfigurationManager.AppSettings["selectP"], conn);
                    _parentAdapter.Fill(_dsP, ConfigurationManager.AppSettings["tableP"]);
                    _bsParent = new BindingSource();
                    _bsParent.DataSource = _dsP.Tables[ConfigurationManager.AppSettings["tableP"]];
                    tableParent.DataSource = _bsParent;
                    tableParent.Rows[0].Selected = true;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void TableParent_SelectionChanged(object sender, EventArgs e)
        {
            try
            {
                _dsC.Clear();
                using (SqlConnection connection = new SqlConnection(_connectionString))
                {
                    _selectCommand = new SqlCommand(ConfigurationManager.AppSettings["selectC"], connection);
                    if (tableParent.SelectedRows.Count > 0)
                    {
                        object departament = tableParent.SelectedRows[0].Cells[0].Value;
                        _selectCommand.Parameters.AddWithValue("@id", departament);
                        _childAdapter = new SqlDataAdapter(_selectCommand);
                        _childAdapter.Fill(_dsC, ConfigurationManager.AppSettings["tableC"]);
                        _bsChild = new BindingSource();
                        _bsChild.DataSource = _dsC.Tables[ConfigurationManager.AppSettings["tableC"]];
                        tableChild.DataSource = _bsChild;
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(_connectionString))
                {
                    connection.Open();
                    object id = tableChild.SelectedRows[0].Cells[0].Value;
                    object departament = tableParent.SelectedRows[0].Cells[0].Value;
                    _selectCommand = new SqlCommand(ConfigurationManager.AppSettings["selectC"], connection);
                    _selectCommand.Parameters.AddWithValue("@id", departament);
                    SqlCommand deleteCommand = new SqlCommand(ConfigurationManager.AppSettings["deleteC"],
                        connection);
                    deleteCommand.Parameters.AddWithValue("@id", id);
                    var nr = deleteCommand.ExecuteNonQuery();
                    if (nr < 0)
                    {
                        throw new Exception("Nu s-a putut fac stergerea!");
                    }

                    _dsC.Tables[ConfigurationManager.AppSettings["tableC"]].Clear();

                    _childAdapter = new SqlDataAdapter(_selectCommand);
                    _childAdapter.Fill(_dsC, ConfigurationManager.AppSettings["tableC"]);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void BtnUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(_connectionString))
                {
                    connection.Open();
                    object id = tableChild.SelectedRows[0].Cells[0].Value;
                    object departament = tableParent.SelectedRows[0].Cells[0].Value;
                    var text = textBoxName.Text;
                    _selectCommand = new SqlCommand(ConfigurationManager.AppSettings["selectC"], connection);
                    _selectCommand.Parameters.AddWithValue("@id", departament);
                    SqlCommand updateCommand = new SqlCommand(ConfigurationManager.AppSettings["updateC"],
                        connection);
                    updateCommand.Parameters.AddWithValue("@id", id);
                    updateCommand.Parameters.AddWithValue("@nume", text);
                    var nr = updateCommand.ExecuteNonQuery();
                    if (nr < 0)
                    {
                        throw new Exception("Nu s-a putut fac Update!");
                    }

                    _dsC.Tables[ConfigurationManager.AppSettings["tableC"]].Clear();

                    _childAdapter = new SqlDataAdapter(_selectCommand);
                    _childAdapter.Fill(_dsC, ConfigurationManager.AppSettings["tableC"]);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(_connectionString))
                {
                    connection.Open();
                    object departament = tableParent.SelectedRows[0].Cells[0].Value;
                    var text = textBoxAddName.Text;
                    _selectCommand = new SqlCommand(ConfigurationManager.AppSettings["selectC"], connection);
                    _selectCommand.Parameters.AddWithValue("@id", departament);
                    SqlCommand insertCommand = new SqlCommand(ConfigurationManager.AppSettings["insertC"],
                        connection);
                    insertCommand.Parameters.AddWithValue("@f_id", departament);
                    insertCommand.Parameters.AddWithValue("@nume", text);
                    var nr = insertCommand.ExecuteNonQuery();
                    if (nr < 0)
                    {
                        throw new Exception("Nu s-a putut fac inserarea!");
                    }

                    _dsC.Tables[ConfigurationManager.AppSettings["tableC"]].Clear();

                    _childAdapter = new SqlDataAdapter(_selectCommand);
                    _childAdapter.Fill(_dsC, ConfigurationManager.AppSettings["tableC"]);
                    if (tableChild.Rows.Count > 0)
                    {
                        tableChild.ClearSelection();
                        tableChild.Rows[0].Selected = true;
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }
    }
}