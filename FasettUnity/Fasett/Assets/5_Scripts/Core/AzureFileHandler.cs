using System;
using System.Collections.Generic;
using System.IO;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.File;
using UnityEngine;

#if WINDOWS_UWP
using Windows.Storage;
#endif

public class AzureFileHandler {
    private string ConnectionString = "DefaultEndpointsProtocol=http;AccountName=fasett;AccountKey=wosKPyTLtLX3gjC2EJ9517s7IjECkB8WFKDQo3Dyn0uqSyZj8CdhtuDlPX7EHM/kTov4ENNkJ9YWiLk7koBMew==;EndpointSuffix=core.windows.net";
    private CloudStorageAccount StorageAccount;

    public AzureFileHandler() {
        StorageAccount = CloudStorageAccount.Parse(ConnectionString);
    }

    public async void UploadFile(string nameOfFile, string localDirectory, string shareName, string remoteDirectory, Action callback) {
        // Create a file client for interacting with the file service.
        CloudFileClient fileClient = StorageAccount.CreateCloudFileClient();

        // Create a share for organizing files and directories within the storage account.
        CloudFileShare share = fileClient.GetShareReference(shareName.ToLower());

        try {
            await share.CreateIfNotExistsAsync();
        }
        catch(StorageException) {
            Debug.LogWarning("[Azure File Handler] Could not create file, please make sure storage account has storage file endpoint enabled and specified correctly in the app.config.");
            throw;
        }

        // Get a reference to the root directory of the share.        
        CloudFileDirectory root = share.GetRootDirectoryReference();

        // Create a directory under the root directory
        CloudFileDirectory dir = root.GetDirectoryReference(remoteDirectory.ToLower());
        await dir.CreateIfNotExistsAsync();

        // Uploading a local file to the directory created above
        CloudFile file = dir.GetFileReference(nameOfFile);

#if WINDOWS_UWP
		StorageFolder storageFolder = await StorageFolder.GetFolderFromPathAsync(localDirectory);
		StorageFile sf = await storageFolder.GetFileAsync(nameOfFile);
		await file.UploadFromFileAsync(sf);
#else
        await file.UploadFromFileAsync(Path.Combine(localDirectory, nameOfFile));
#endif

        // List all files/directories under the root directory
        List<IListFileItem> results = new List<IListFileItem>();
        FileContinuationToken token = null;
        do {
            FileResultSegment resultSegment = await share.GetRootDirectoryReference().ListFilesAndDirectoriesSegmentedAsync(token);
            results.AddRange(resultSegment.Results);
            token = resultSegment.ContinuationToken;
        }
        while(token != null);

        // Print all files/directories listed above
        foreach(IListFileItem listItem in results) {
            // listItem type will be CloudFile or CloudFileDirectory
            Debug.Log(string.Format("- {0} (type: {1})", listItem.Uri, listItem.GetType()));
        }

        if (callback != null) {
            callback();
        }
    }

    public async void DownloadFile(string nameOfFile, string localDirectory, string shareName, string remoteDirectory, Action<bool> callback) {
        bool downloadSucceeded = false;
        try {
            // Create a file client for interacting with the file service.
            CloudFileClient fileClient = StorageAccount.CreateCloudFileClient();

            // Create a share for organizing files and directories within the storage account.
            CloudFileShare share = fileClient.GetShareReference(shareName.ToLower());

            // Get a reference to the root directory of the share.        
            CloudFileDirectory root = share.GetRootDirectoryReference();

            // Get the directory under the root directory
            CloudFileDirectory dir = root.GetDirectoryReference(remoteDirectory.ToLower());

            // Get the remote file
            CloudFile file = dir.GetFileReference(nameOfFile);

#if WINDOWS_UWP
		    StorageFolder storageFolder = await StorageFolder.GetFolderFromPathAsync(localDirectory);
            StorageFile sf = await storageFolder.CreateFileAsync(nameOfFile, CreationCollisionOption.ReplaceExisting);
		    await file.DownloadToFileAsync(sf);
#else
            string path = Path.Combine(Application.temporaryCachePath, nameOfFile);
            await file.DownloadToFileAsync(path, FileMode.Create);
#endif
            downloadSucceeded = true;
        }
        catch {
            downloadSucceeded = false;
        }
        if (callback != null) {
            callback(downloadSucceeded);
        }
    }
}

