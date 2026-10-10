#pragma once

namespace ComponentesConexas {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	// Un paso del algoritmo: texto explicativo + estado de los nodos en ese momento
	public ref class Paso {
	public:
		String^ texto;
		array<int>^ comp;   // componente de cada nodo (-1 = no visitado)
		int actual;         // nodo analizado en este paso (-1 = ninguno)
	};

	/// <summary>
	/// Formulario principal
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			// Inicializacion de datos propios
			//
			n = 0;
			seleccionado = -1;
			modoManual = false;
			nodoActual = -1;
			idxPaso = 0;
			paleta = gcnew array<Color>{
				Color::Tomato, Color::SteelBlue, Color::MediumSeaGreen, Color::Orange,
					Color::MediumPurple, Color::HotPink, Color::Goldenrod, Color::Teal,
					Color::SaddleBrown, Color::DarkOliveGreen, Color::Crimson, Color::DodgerBlue };
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

		// ---------------- Controles (los ve el diseñador) ----------------
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::NumericUpDown^ nudN;
	private: System::Windows::Forms::Button^ btnCrear;
	private: System::Windows::Forms::Button^ btnManual;
	private: System::Windows::Forms::Button^ btnAleatorio;
	private: System::Windows::Forms::Button^ btnIniciar;
	private: System::Windows::Forms::Button^ btnSiguiente;
	private: System::Windows::Forms::Button^ btnTodo;
	private: System::Windows::Forms::Label^ lblInfo;
	private: System::Windows::Forms::Panel^ panelGrafo;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtMatriz;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtLog;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ txtResultado;

	private:
		System::ComponentModel::Container^ components;

		// ---------------- Datos propios ----------------
	private:
		int n;
		array<int, 2>^ ady;
		array<Point>^ pos;
		int seleccionado;
		bool modoManual;

		List<Paso^>^ pasos;
		List<List<int>^>^ componentes;
		int idxPaso;
		array<int>^ compActual;
		int nodoActual;
		array<Color>^ paleta;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metodo necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este metodo con el editor de codigo.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->nudN = (gcnew System::Windows::Forms::NumericUpDown());
			this->btnCrear = (gcnew System::Windows::Forms::Button());
			this->btnManual = (gcnew System::Windows::Forms::Button());
			this->btnAleatorio = (gcnew System::Windows::Forms::Button());
			this->btnIniciar = (gcnew System::Windows::Forms::Button());
			this->btnSiguiente = (gcnew System::Windows::Forms::Button());
			this->btnTodo = (gcnew System::Windows::Forms::Button());
			this->lblInfo = (gcnew System::Windows::Forms::Label());
			this->panelGrafo = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtMatriz = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtLog = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtResultado = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudN))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(147, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Cantidad de nodos (4-12):";
			// 
			// nudN
			// 
			this->nudN->Location = System::Drawing::Point(180, 14);
			this->nudN->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 12, 0, 0, 0 });
			this->nudN->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			this->nudN->Name = L"nudN";
			this->nudN->Size = System::Drawing::Size(50, 22);
			this->nudN->TabIndex = 1;
			this->nudN->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
			// 
			// btnCrear
			// 
			this->btnCrear->Location = System::Drawing::Point(240, 11);
			this->btnCrear->Name = L"btnCrear";
			this->btnCrear->Size = System::Drawing::Size(90, 28);
			this->btnCrear->TabIndex = 2;
			this->btnCrear->Text = L"Crear grafo";
			this->btnCrear->UseVisualStyleBackColor = true;
			this->btnCrear->Click += gcnew System::EventHandler(this, &MyForm::btnCrear_Click);
			// 
			// btnManual
			// 
			this->btnManual->Enabled = false;
			this->btnManual->Location = System::Drawing::Point(340, 11);
			this->btnManual->Name = L"btnManual";
			this->btnManual->Size = System::Drawing::Size(80, 28);
			this->btnManual->TabIndex = 3;
			this->btnManual->Text = L"Manual";
			this->btnManual->UseVisualStyleBackColor = true;
			this->btnManual->Click += gcnew System::EventHandler(this, &MyForm::btnManual_Click);
			// 
			// btnAleatorio
			// 
			this->btnAleatorio->Enabled = false;
			this->btnAleatorio->Location = System::Drawing::Point(425, 11);
			this->btnAleatorio->Name = L"btnAleatorio";
			this->btnAleatorio->Size = System::Drawing::Size(80, 28);
			this->btnAleatorio->TabIndex = 4;
			this->btnAleatorio->Text = L"Aleatorio";
			this->btnAleatorio->UseVisualStyleBackColor = true;
			this->btnAleatorio->Click += gcnew System::EventHandler(this, &MyForm::btnAleatorio_Click);
			// 
			// btnIniciar
			// 
			this->btnIniciar->Enabled = false;
			this->btnIniciar->Location = System::Drawing::Point(515, 11);
			this->btnIniciar->Name = L"btnIniciar";
			this->btnIniciar->Size = System::Drawing::Size(120, 28);
			this->btnIniciar->TabIndex = 5;
			this->btnIniciar->Text = L"Iniciar algoritmo";
			this->btnIniciar->UseVisualStyleBackColor = true;
			this->btnIniciar->Click += gcnew System::EventHandler(this, &MyForm::btnIniciar_Click);
			// 
			// btnSiguiente
			// 
			this->btnSiguiente->Enabled = false;
			this->btnSiguiente->Location = System::Drawing::Point(645, 11);
			this->btnSiguiente->Name = L"btnSiguiente";
			this->btnSiguiente->Size = System::Drawing::Size(110, 28);
			this->btnSiguiente->TabIndex = 6;
			this->btnSiguiente->Text = L"Siguiente paso";
			this->btnSiguiente->UseVisualStyleBackColor = true;
			this->btnSiguiente->Click += gcnew System::EventHandler(this, &MyForm::btnSiguiente_Click);
			// 
			// btnTodo
			// 
			this->btnTodo->Enabled = false;
			this->btnTodo->Location = System::Drawing::Point(765, 11);
			this->btnTodo->Name = L"btnTodo";
			this->btnTodo->Size = System::Drawing::Size(110, 28);
			this->btnTodo->TabIndex = 7;
			this->btnTodo->Text = L"Ejecutar todo";
			this->btnTodo->UseVisualStyleBackColor = true;
			this->btnTodo->Click += gcnew System::EventHandler(this, &MyForm::btnTodo_Click);
			// 
			// lblInfo
			// 
			this->lblInfo->AutoSize = true;
			this->lblInfo->Location = System::Drawing::Point(12, 48);
			this->lblInfo->Name = L"lblInfo";
			this->lblInfo->Size = System::Drawing::Size(200, 17);
			this->lblInfo->TabIndex = 8;
			this->lblInfo->Text = L"Elige n y pulsa \'Crear grafo\'.";
			// 
			// panelGrafo
			// 
			this->panelGrafo->BackColor = System::Drawing::Color::White;
			this->panelGrafo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelGrafo->Location = System::Drawing::Point(12, 72);
			this->panelGrafo->Name = L"panelGrafo";
			this->panelGrafo->Size = System::Drawing::Size(500, 450);
			this->panelGrafo->TabIndex = 9;
			this->panelGrafo->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panelGrafo_Paint);
			this->panelGrafo->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::panelGrafo_MouseClick);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(522, 52);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(135, 17);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Matriz de adyacencia:";
			// 
			// txtMatriz
			// 
			this->txtMatriz->Font = (gcnew System::Drawing::Font(L"Consolas", 10));
			this->txtMatriz->Location = System::Drawing::Point(522, 72);
			this->txtMatriz->Multiline = true;
			this->txtMatriz->Name = L"txtMatriz";
			this->txtMatriz->ReadOnly = true;
			this->txtMatriz->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->txtMatriz->Size = System::Drawing::Size(470, 230);
			this->txtMatriz->TabIndex = 11;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(522, 312);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(131, 17);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Pasos del algoritmo:";
			// 
			// txtLog
			// 
			this->txtLog->Location = System::Drawing::Point(522, 332);
			this->txtLog->Multiline = true;
			this->txtLog->Name = L"txtLog";
			this->txtLog->ReadOnly = true;
			this->txtLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtLog->Size = System::Drawing::Size(470, 190);
			this->txtLog->TabIndex = 13;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 532);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(70, 17);
			this->label4->TabIndex = 14;
			this->label4->Text = L"Resultado:";
			// 
			// txtResultado
			// 
			this->txtResultado->Font = (gcnew System::Drawing::Font(L"Consolas", 10));
			this->txtResultado->Location = System::Drawing::Point(12, 552);
			this->txtResultado->Multiline = true;
			this->txtResultado->Name = L"txtResultado";
			this->txtResultado->ReadOnly = true;
			this->txtResultado->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtResultado->Size = System::Drawing::Size(980, 120);
			this->txtResultado->TabIndex = 15;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1004, 685);
			this->Controls->Add(this->txtResultado);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->txtLog);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txtMatriz);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->panelGrafo);
			this->Controls->Add(this->lblInfo);
			this->Controls->Add(this->btnTodo);
			this->Controls->Add(this->btnSiguiente);
			this->Controls->Add(this->btnIniciar);
			this->Controls->Add(this->btnAleatorio);
			this->Controls->Add(this->btnManual);
			this->Controls->Add(this->btnCrear);
			this->Controls->Add(this->nudN);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Componentes conexas de un grafo";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudN))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// ============================================================
		//  EVENTOS DE BOTONES
		// ============================================================
	private: System::Void btnCrear_Click(System::Object^ sender, System::EventArgs^ e) {
		n = Convert::ToInt32(nudN->Value);
		ady = gcnew array<int, 2>(n, n);
		pos = gcnew array<Point>(n);
		compActual = gcnew array<int>(n);
		for (int i = 0; i < n; i++) compActual[i] = -1;
		nodoActual = -1;
		seleccionado = -1;
		modoManual = false;

		// Nodos distribuidos en circulo
		double cx = panelGrafo->Width / 2.0;
		double cy = panelGrafo->Height / 2.0;
		double r = 180;
		for (int i = 0; i < n; i++) {
			double ang = 2 * Math::PI * i / n - Math::PI / 2;
			pos[i] = Point((int)(cx + r * Math::Cos(ang)), (int)(cy + r * Math::Sin(ang)));
		}

		btnManual->Enabled = true;
		btnAleatorio->Enabled = true;
		btnIniciar->Enabled = false;
		btnSiguiente->Enabled = false;
		btnTodo->Enabled = false;
		txtLog->Clear();
		txtResultado->Clear();
		ActualizarMatriz();
		lblInfo->Text = "Elige 'Manual' o 'Aleatorio'.";
		panelGrafo->Invalidate();
	}

	private: System::Void btnManual_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) ady[i, j] = 0;
		ReiniciarEstado();
		modoManual = true;
		btnIniciar->Enabled = true;
		lblInfo->Text = "Modo manual: clic en un nodo y luego en otro para crear/quitar una arista; clic dos veces en el mismo nodo para crear/quitar un lazo.";
		ActualizarMatriz();
		panelGrafo->Invalidate();
	}

	private: System::Void btnAleatorio_Click(System::Object^ sender, System::EventArgs^ e) {
		Random^ rnd = gcnew Random();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) ady[i, j] = 0;
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++) {                 // j = i incluye la diagonal (lazos)
				double prob = (i == j) ? 0.1 : 0.2;       // lazo menos probable
				if (rnd->NextDouble() < prob) {
					ady[i, j] = 1;
					ady[j, i] = 1;
				}
			}
		ReiniciarEstado();
		modoManual = false;
		btnIniciar->Enabled = true;
		lblInfo->Text = "Grafo aleatorio generado. Pulsa 'Iniciar algoritmo'.";
		ActualizarMatriz();
		panelGrafo->Invalidate();
	}

	private: System::Void btnIniciar_Click(System::Object^ sender, System::EventArgs^ e) {
		modoManual = false;          // ya no se puede editar el grafo
		seleccionado = -1;
		GenerarPasos();
		idxPaso = 0;
		for (int i = 0; i < n; i++) compActual[i] = -1;
		nodoActual = -1;
		txtLog->Clear();
		txtResultado->Clear();
		btnSiguiente->Enabled = true;
		btnTodo->Enabled = true;
		btnIniciar->Enabled = false;
		lblInfo->Text = "Pulsa 'Siguiente paso' para avanzar.";
		panelGrafo->Invalidate();
	}

	private: System::Void btnSiguiente_Click(System::Object^ sender, System::EventArgs^ e) {
		AvanzarPaso();
	}

	private: System::Void btnTodo_Click(System::Object^ sender, System::EventArgs^ e) {
		while (idxPaso < pasos->Count) AvanzarPaso();
	}

		   // ============================================================
		   //  ALGORITMO (DFS con pila). Se guardan todos los pasos y luego
		   //  el usuario los recorre uno por uno.
		   // ============================================================
	private: void GuardarPaso(String^ texto, array<int>^ comp, int actual) {
		Paso^ p = gcnew Paso();
		p->texto = texto;
		p->comp = (array<int>^)comp->Clone();
		p->actual = actual;
		pasos->Add(p);
	}

	private: void GenerarPasos() {
		pasos = gcnew List<Paso^>();
		componentes = gcnew List<List<int>^>();
		array<int>^ comp = gcnew array<int>(n);
		for (int i = 0; i < n; i++) comp[i] = -1;
		int c = 0;

		for (int i = 0; i < n; i++) {
			if (comp[i] != -1) {
				GuardarPaso("Nodo " + (i + 1).ToString() + " ya fue visitado. Se omite.", comp, i);
				continue;
			}
			GuardarPaso("Nodo " + (i + 1).ToString() + " no visitado: se inicia la componente " + (c + 1).ToString() + ".", comp, i);
			List<int>^ lista = gcnew List<int>();
			System::Collections::Generic::Stack<int>^ pila = gcnew System::Collections::Generic::Stack<int>();
			comp[i] = c;
			pila->Push(i);
			lista->Add(i);

			while (pila->Count > 0) {
				int u = pila->Pop();
				GuardarPaso("Se analiza el nodo " + (u + 1).ToString() + " (se revisan sus vecinos).", comp, u);
				for (int v = 0; v < n; v++) {
					if (ady[u, v] == 1 && comp[v] == -1) {
						comp[v] = c;
						pila->Push(v);
						lista->Add(v);
						GuardarPaso("  Vecino " + (v + 1).ToString() + " descubierto desde " + (u + 1).ToString() +
							": pertenece a la componente " + (c + 1).ToString() + ".", comp, v);
					}
				}
			}
			lista->Sort();
			componentes->Add(lista);
			GuardarPaso("Componente " + (c + 1).ToString() + " completa.", comp, -1);
			c++;
		}
	}

	private: void AvanzarPaso() {
		if (pasos == nullptr || idxPaso >= pasos->Count) return;
		Paso^ p = pasos[idxPaso];
		txtLog->AppendText((idxPaso + 1).ToString() + ". " + p->texto + Environment::NewLine);
		compActual = (array<int>^)p->comp->Clone();
		nodoActual = p->actual;
		idxPaso++;

		if (idxPaso >= pasos->Count) {
			btnSiguiente->Enabled = false;
			btnTodo->Enabled = false;
			btnIniciar->Enabled = true;
			nodoActual = -1;
			MostrarResultado();
			lblInfo->Text = "Algoritmo terminado.";
		}
		panelGrafo->Invalidate();
	}

	private: void MostrarResultado() {
		StringBuilder^ sb = gcnew StringBuilder();
		sb->AppendLine("Numero de componentes conexas: " + componentes->Count.ToString());
		for (int k = 0; k < componentes->Count; k++) {
			sb->Append("  Componente " + (k + 1).ToString() + ": { ");
			for (int j = 0; j < componentes[k]->Count; j++) {
				if (j > 0) sb->Append(", ");
				sb->Append((componentes[k][j] + 1).ToString());
			}
			sb->AppendLine(" }");
		}
		txtResultado->Text = sb->ToString();
	}

		   // ============================================================
		   //  AUXILIARES
		   // ============================================================
	private: void ReiniciarEstado() {
		for (int i = 0; i < n; i++) compActual[i] = -1;
		nodoActual = -1;
		idxPaso = 0;
		pasos = nullptr;
		txtLog->Clear();
		txtResultado->Clear();
		btnSiguiente->Enabled = false;
		btnTodo->Enabled = false;
	}

	private: void ActualizarMatriz() {
		StringBuilder^ sb = gcnew StringBuilder();
		sb->Append("    ");
		for (int j = 0; j < n; j++) sb->Append((j + 1).ToString()->PadLeft(3));
		sb->AppendLine();
		for (int i = 0; i < n; i++) {
			sb->Append((i + 1).ToString()->PadLeft(3) + " ");
			for (int j = 0; j < n; j++) sb->Append(ady[i, j].ToString()->PadLeft(3));
			sb->AppendLine();
		}
		txtMatriz->Text = sb->ToString();
	}

		   // ============================================================
		   //  DIBUJO DEL GRAFO
		   // ============================================================
	private: System::Void panelGrafo_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		if (n == 0) return;
		Graphics^ g = e->Graphics;
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		// Aristas
		Pen^ lapiz = gcnew Pen(Color::Gray, 2);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (ady[i, j] == 1) g->DrawLine(lapiz, pos[i], pos[j]);

		// Lazos (un nodo apuntandose a si mismo)
		for (int i = 0; i < n; i++) {
			if (ady[i, i] == 1) {
				double dx = pos[i].X - panelGrafo->Width / 2.0;
				double dy = pos[i].Y - panelGrafo->Height / 2.0;
				double len = Math::Sqrt(dx * dx + dy * dy);
				if (len < 1) len = 1;
				dx /= len; dy /= len;
				int rl = 12;                                   // radio del lazo
				int cx = (int)(pos[i].X + dx * (18 + rl - 4));
				int cy = (int)(pos[i].Y + dy * (18 + rl - 4));
				g->DrawEllipse(lapiz, cx - rl, cy - rl, 2 * rl, 2 * rl);
			}
		}

		// Nodos
		int R = 18;
		System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
		for (int i = 0; i < n; i++) {
			Color col = Color::LightGray;
			if (compActual != nullptr && compActual[i] >= 0)
				col = paleta[compActual[i] % paleta->Length];

			Rectangle rect(pos[i].X - R, pos[i].Y - R, 2 * R, 2 * R);
			g->FillEllipse(gcnew SolidBrush(col), rect);

			Pen^ borde = gcnew Pen(Color::Black, 2);
			if (i == nodoActual) borde = gcnew Pen(Color::Red, 4);
			else if (i == seleccionado) borde = gcnew Pen(Color::Blue, 4);
			g->DrawEllipse(borde, rect);

			String^ txt = (i + 1).ToString();
			SizeF tam = g->MeasureString(txt, fuente);
			g->DrawString(txt, fuente, Brushes::Black,
				pos[i].X - tam.Width / 2, pos[i].Y - tam.Height / 2);
		}
	}

	private: System::Void panelGrafo_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (!modoManual || n == 0) return;
		int R = 18;
		for (int i = 0; i < n; i++) {
			int dx = e->X - pos[i].X;
			int dy = e->Y - pos[i].Y;
			if (dx * dx + dy * dy <= R * R) {
				if (seleccionado == -1) {
					seleccionado = i;
				}
				else {
					// Alterna arista; si seleccionado == i, alterna el lazo ady[i, i]
					int nuevo = 1 - ady[seleccionado, i];
					ady[seleccionado, i] = nuevo;
					ady[i, seleccionado] = nuevo;
					ActualizarMatriz();
					seleccionado = -1;
				}
				panelGrafo->Invalidate();
				return;
			}
		}
		seleccionado = -1;
		panelGrafo->Invalidate();
	}
	};
}