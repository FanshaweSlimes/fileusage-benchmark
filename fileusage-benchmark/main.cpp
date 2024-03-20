/*
\file:		main.cpp
\author:	Jared Gajulin
\date:		Mar 19, 2024
\version:	1.0.0
\brief:		Benchmarks the fileusage binary against the provided demo binary. Files must be named fileusage.exe & fileusage-demo.exe respectively.
*/

#include <iostream>
#include <chrono>

#include <windows.h>
#include <filesystem>

#include <cstdlib>

void benchmark(std::wstringstream& wss, const wchar_t* application_name, const int argc, const std::string& root_dir, const bool no_cout = false)
{
	if (!no_cout)
		wss << application_name << ":\n";

	STARTUPINFO si{};
	si.cb = sizeof(si);

	PROCESS_INFORMATION pi;

	std::wstring args = std::filesystem::current_path().wstring().append(L"\\").append(application_name)
		.append(L"\"").append(L" ");

	if (argc > 1)
	{
		const std::wstring root_dir_w(root_dir.begin(), root_dir.end());
		args.append(root_dir_w);
	}
	else args.append(L"");

	args.insert(0, L"\"");

	const HANDLE h_null = CreateFile(L"NUL", GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (no_cout)
	{
		si.dwFlags = STARTF_USESTDHANDLES;

		si.hStdOutput = h_null;
		si.hStdError = h_null;
	}

	const auto start_time = std::chrono::high_resolution_clock::now();
	if (const wchar_t* args_wchar = args.c_str(); !CreateProcess(application_name,
		const_cast<LPWSTR>(args_wchar),
		nullptr,
		nullptr,
		FALSE,
		0,
		nullptr,
		nullptr,
		&si, // lpStartupInfo
		&pi  // lpProcessInformation
	))
	{
		wss << "\t" << application_name << " not found.\n\n";

		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	const auto end_time = std::chrono::high_resolution_clock::now();

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(h_null);

	const auto diff = end_time - start_time;

	const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
	const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(diff);
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
	const long double seconds = static_cast<long double>(nanoseconds.count()) / 1000000000.0;

	wss << "\tExecution time info";

	if (no_cout)
	{
		wss << " (cout disabled)";
	}

	wss << ":\n";

	wss << "\t\tNanoseconds: " << nanoseconds << "\n"
		<< "\t\tMicroseconds: " << microseconds << "\n"
		<< "\t\tMilliseconds: " << milliseconds << "\n"
		<< "\t\tSeconds: " << seconds << 's' << '\n';

	wss << '\n';

	if (!no_cout)
	{
		benchmark(wss, application_name, argc, root_dir, true);
	}
}

int main(const int argc, const char** argv)
{
	std::wstringstream wss;
	wss.imbue(std::locale(""));

	std::filesystem::path root_dir_path{ "." };
	const std::string root_dir = argc > 1 ? argv[1] : "";

	if (argc > 1)
	{
		root_dir_path.assign(root_dir);
	}

	for (const auto& application_name : { L"fileusage.exe", L"fileusage-demo.exe" })
	{
		benchmark(wss, application_name, argc, root_dir);
	}

	system("cls");

	std::cout << "fileusage_benchmark {v1.0.0} (c) 2024, Jared Gajulin" << "\n";
	std::cout << "Root directory is: " << absolute(root_dir_path) << "\n\n";

	std::wcout << wss.str();

	return EXIT_SUCCESS;
}
